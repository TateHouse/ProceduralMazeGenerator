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

#include "Utility/DeltaTimeCalculator.hpp"
#include "Utility/UnitScale.hpp"
#include "BinaryTreeMazeGenerator.hpp"
#include "MazeRenderer.hpp"
#include "Shader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"
#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"
#include "Window.hpp"

static constexpr auto WINDOW_WIDTH {1280};
static constexpr auto WINDOW_HEIGHT {720};
static constexpr auto WINDOW_TITLE {"Procedural Maze Generator Renderer"};
static constexpr auto SQUARE_GRID_SIZE {20};
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

    auto projection {createOrthographicProjection(static_cast<float>(window.getWidth()) * Renderer::Utility::UNIT_SCALE,
                                                  static_cast<float>(window.getHeight()) *
                                                  Renderer::Utility::UNIT_SCALE, -1.0f, 1.0f)};

    auto cellSize {25.0f * Renderer::Utility::UNIT_SCALE};
    auto backgroundColor {glm::vec3(0.0f, 0.0f, 0.0f)};
    auto gridColor {glm::vec3(1.0f, 1.0f, 1.0f)};
    auto gridLineThickness {MIN_GRID_LINE_THICKNESS};

    auto squareGrid {Core::SquareGrid {SQUARE_GRID_SIZE}};
    squareGrid.initialize();

    auto sidewinderMazeGenerator {Core::SidewinderMazeGenerator {}};
    sidewinderMazeGenerator.generate(&squareGrid, nullptr);

    auto mazeRenderer {Renderer::MazeRenderer {&squareGrid, cellSize}};
    mazeRenderer.updateVertices();

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

        if (ImGui::Button("Update Maze")) {
            mazeRenderer.updateVertices();
        }

        ImGui::InputFloat("Cell Size", &cellSize);
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

        const auto aspectRatio {static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight())};
        mazeRenderer.update(deltaTimeCalculator.getDeltaTime(), cellSize, gridLineThickness, aspectRatio, gridColor);

        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mazeRenderer.render(projection);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.render();
    }

    mazeRenderer.destroy();
    window.close();
    glfwTerminate();

    return 0;
}