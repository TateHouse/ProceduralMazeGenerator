#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <format>
#include <iostream>

#include "BinaryTreeMazeGenerator.hpp"
#include "Utility/DeltaTimeCalculator.hpp"
#include "Shader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"
#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"
#include "Window.hpp"

static constexpr auto WINDOW_WIDTH {1280};
static constexpr auto WINDOW_HEIGHT {720};
static constexpr auto WINDOW_TITLE {"Procedural Maze Generator Renderer"};

static constexpr auto UNIT_SCALE {0.01f}; // 1 unit = 1 cm

static constexpr auto SQUARE_GRID_SIZE {20};
static constexpr auto CELL_SIZE {25.0f * UNIT_SCALE};
static constexpr auto MIN_GRID_LINE_THICKNESS {0.002f};
static constexpr auto MAX_GRID_LINE_THICKNESS {0.03f};

glm::mat4 createOrthographicProjection(const float width,
                                       const float height,
                                       const float near,
                                       const float far) noexcept {
    const auto left {-width * 0.5f};
    const auto right {width * 0.5f};
    const auto top {height * 0.5f};
    const auto bottom {-height * 0.5f};

    return glm::ortho(left, right, bottom, top, near, far);
}

void insertNorthernWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
    vertices.push_back(-halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}

void insertWesternWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
    vertices.push_back(-halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(-halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}

void insertSouthernWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
    vertices.push_back(-halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
}

void insertEasternWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
    vertices.push_back(halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}

int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << '\n';
        return -1;
    }

    auto window {Renderer::Window {WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE}};
    if (!window.initialize()) {
        std::cerr << "ERROR: Failed to initialize window" << '\n';
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "ERROR: Failed to initialize GLAD" << '\n';
        window.close();
        glfwTerminate();
        return -1;
    }

    window.setCallbacks();

    auto projection {createOrthographicProjection(static_cast<float>(window.getWidth()) * UNIT_SCALE,
                                                  static_cast<float>(window.getHeight()) * UNIT_SCALE, -1.0f, 1.0f)};

    auto backgroundColor {glm::vec3(0.0f, 0.0f, 0.0f)};
    auto gridColor {glm::vec3(1.0f, 1.0f, 1.0f)};
    auto gridLineThickness {MIN_GRID_LINE_THICKNESS};

    auto squareGrid {Core::SquareGrid {SQUARE_GRID_SIZE}};
    squareGrid.initialize();

    auto sidewinderMazeGenerator {Core::SidewinderMazeGenerator {}};
    sidewinderMazeGenerator.generate(&squareGrid, nullptr);

    std::vector<float> vertices {};
    const auto [gridWidth, gridHeight] {squareGrid.getSize()};
    const auto cellCount {gridWidth * gridHeight};
    vertices.reserve(cellCount * 3);

    GLuint vao {0};
    GLuint vbo {0};

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    const auto halfWidth {gridWidth * CELL_SIZE * 0.5f};
    const auto halfHeight {gridHeight * CELL_SIZE * 0.5f};

    for (auto row {gridHeight - 1}; row >= 0; --row) {
        for (auto column {0}; column < gridWidth; ++column) {
            const auto xGridPosition {static_cast<int>(column)};
            const auto yGridPosition {static_cast<int>(row)};
            const auto* const cell {squareGrid[{xGridPosition, yGridPosition}]};

            const auto xCoordinate {static_cast<float>(xGridPosition * CELL_SIZE) - halfWidth};
            const auto yCoordinate {static_cast<float>(yGridPosition * CELL_SIZE) - halfHeight};

            const auto* const eastNeighbor {cell->getEast()};
            const auto* const southNeighbor {cell->getSouth()};

            if (!cell->isLinked(eastNeighbor)) {
                vertices.push_back(xCoordinate + CELL_SIZE);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);

                vertices.push_back(xCoordinate + CELL_SIZE);
                vertices.push_back(yCoordinate + CELL_SIZE);
                vertices.push_back(0.0f);
            }

            if (!cell->isLinked(southNeighbor)) {
                vertices.push_back(xCoordinate);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);

                vertices.push_back(xCoordinate + CELL_SIZE);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);
            }
        }
    }

    insertNorthernWallVertices(vertices, halfWidth, halfHeight);
    insertWesternWallVertices(vertices, halfWidth, halfHeight);
    insertSouthernWallVertices(vertices, halfWidth, halfHeight);
    insertEasternWallVertices(vertices, halfWidth, halfHeight);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const auto vertexCount {vertices.size() / 3};

    Renderer::Shader* shader {nullptr};

    try {
        shader = new Renderer::Shader("Shaders/Test.vert", "Shaders/Test.frag", "Shaders/Test.geom");

    } catch (const Renderer::ShaderCompilationException& exception) {
        std::cerr << exception.what() << '\n';
        window.setShouldClose(true);
    } catch (const Renderer::ShaderLinkingException& exception) {
        std::cerr << exception.what() << '\n';
        window.setShouldClose(true);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto& io {ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsLight();

    window.initializeImGui();

    auto deltaTimeCalculator {Renderer::Utility::DeltaTimeCalculator {
            []() noexcept {
                return static_cast<float>(glfwGetTime());
            }
    }};

    while (!window.getShouldClose()) {
        const auto currentFrame {deltaTimeCalculator.update()};

        window.update(deltaTimeCalculator.getDeltaTime());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Maze Generator");
        ImGui::Text("Hello World");
        if (ImGui::Button("Save")) {
            std::cout << "Saved maze!" << '\n';
        }

        ImGui::SliderFloat("Grid Line Thickness", &gridLineThickness, MIN_GRID_LINE_THICKNESS, MAX_GRID_LINE_THICKNESS);

        const auto currentFrameString {std::format("Current Frame: {}", currentFrame)};
        ImGui::Text(currentFrameString.c_str());

        const auto windowWidthString {std::format("Window Width: {}", window.getWidth())};
        ImGui::Text(windowWidthString.c_str());

        const auto windowHeightString {std::format("Window Height: {}", window.getHeight())};
        ImGui::Text(windowHeightString.c_str());

        ImGui::ColorPicker3("Background Color", glm::value_ptr(backgroundColor));
        ImGui::ColorPicker3("Grid Color", glm::value_ptr(gridColor));

        float samples[100];
        for (auto number {0}; number < 100; ++number) {
            samples[number] = std::sinf(number * 0.2f + ImGui::GetTime() * 1.5f);
        }

        ImGui::PlotLines("Samples", samples, 100);

        ImGui::End();

        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (shader != nullptr) {
            shader->use();

            shader->setUniformMatrix4x4fv("projection", projection);

            shader->setUniform1f("lineThickness", gridLineThickness);

            auto aspectRatio {static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight())};
            shader->setUniform1f("aspectRatio", aspectRatio);

            shader->setUniform3fv("color", gridColor);

            glBindVertexArray(vao);
            glDrawArrays(GL_LINES, 0, vertexCount);
            glBindVertexArray(0);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.render();
    }

    delete shader;

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    window.close();
    glfwTerminate();

    return 0;
}