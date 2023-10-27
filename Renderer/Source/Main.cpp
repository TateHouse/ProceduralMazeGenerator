#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <array>
#include <format>
#include <iostream>

#include "Utility/DeltaTimeCalculator.hpp"
#include "Utility/UnitScale.hpp"
#include "BinaryTreeMazeGenerator.hpp"
#include "MazeGenerationAlgorithm.hpp"
#include "MazeRenderer.hpp"
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

    auto binaryTreeMazeGenerator {std::make_unique<Core::BinaryTreeMazeGenerator>()};
    auto sidewinderMazeGenerator {std::make_unique<Core::SidewinderMazeGenerator>()};
    const auto mazeGenerators {std::array<std::unique_ptr<Core::MazeGenerator>, 2> {
            std::move(binaryTreeMazeGenerator),
            std::move(sidewinderMazeGenerator)
    }};

    auto squareGrid {Core::SquareGrid {SQUARE_GRID_SIZE}};
    squareGrid.initialize();

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

    auto selectedMazeGeneratorIndex {0};

    while (!window.getShouldClose()) {
        const auto currentFrame {deltaTimeCalculator.update()};

        window.update(deltaTimeCalculator.getDeltaTime());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Maze Generator");
        if (ImGui::Button("Save")) {
            std::cout << "Saved maze!" << '\n';
        }

        if (ImGui::BeginCombo("Maze Generator",
                              Renderer::getMazeGenerationAlgorithmName(mazeGenerators[selectedMazeGeneratorIndex].get()).c_str())) {
            for (auto index {0}; index < mazeGenerators.size(); ++index) {
                auto isSelected {selectedMazeGeneratorIndex == index};

                if (ImGui::Selectable(Renderer::getMazeGenerationAlgorithmName(mazeGenerators[index].get()).c_str(),
                                      isSelected)) {
                    selectedMazeGeneratorIndex = index;
                }

                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Generate Maze")) {
            squareGrid.reset();
            mazeGenerators[selectedMazeGeneratorIndex]->generate(&squareGrid, nullptr);
            mazeRenderer.updateVertices();
        }

        if (ImGui::Button("Generate Grid")) {
            squareGrid.reset();
            squareGrid.initialize();
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