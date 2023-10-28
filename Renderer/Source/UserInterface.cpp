#include "UserInterface.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <format>

#include "Utility/UnitScale.hpp"

namespace Renderer {
UserInterface::UserInterface(const std::array<std::unique_ptr<Core::MazeGenerator>, 2>& mazeGenerators,
                             MazeRenderer* const mazeRenderer,
                             Core::Grid* const grid,
                             const Window& window) noexcept:
        mazeGenerators {mazeGenerators}, mazeRenderer {mazeRenderer}, grid {grid}, window {window} {

}

UserInterface::~UserInterface() noexcept {
    destroy();
}

void UserInterface::initialize() {
    IMGUI_CHECKVERSION();
    context = ImGui::CreateContext();

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsLight();
}

void UserInterface::update(const float currentFrame) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Maze Generator");

    if (ImGui::Button("Generate Maze")) {
        grid->reset();
        mazeGenerators[selectedMazeGeneratorIndex]->generate(grid, nullptr);
        mazeRenderer->updateVertices();
    }

    if (ImGui::Button("Generate Grid")) {
        grid->reset();
        grid->initialize();
        mazeRenderer->updateVertices();
    }

    auto generatorName {mazeGenerators[selectedMazeGeneratorIndex]->getMazeGenerationAlgorithmName()};
    if (ImGui::BeginCombo("Maze Generator", generatorName.c_str())) {
        for (auto index {0}; index < mazeGenerators.size(); ++index) {
            auto isSelected {selectedMazeGeneratorIndex == index};

            generatorName = mazeGenerators[index]->getMazeGenerationAlgorithmName();
            if (ImGui::Selectable(generatorName.c_str(), isSelected)) {
                selectedMazeGeneratorIndex = index;
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    ImGui::InputFloat("Cell Size", &Utility::cellSize);
    ImGui::SliderFloat("Grid Line Thickness",
                       &Utility::gridLineThickness,
                       Utility::MIN_GRID_LINE_THICKNESS,
                       Utility::MAX_GRID_LINE_THICKNESS);
    ImGui::ColorPicker3("Background Color", glm::value_ptr(backgroundColor));
    ImGui::ColorPicker3("Grid Color", glm::value_ptr(gridColor));

    const auto currentFrameString {std::format("Current Frame: {}", currentFrame)};
    ImGui::Text(currentFrameString.c_str());

    const auto windowWidthString {std::format("Window Width: {}", window.getWidth())};
    ImGui::Text(windowWidthString.c_str());

    const auto windowHeightString {std::format("Window Height: {}", window.getHeight())};
    ImGui::Text(windowHeightString.c_str());

    ImGui::End();
}

void UserInterface::render() const {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    context = nullptr;
    io = nullptr;
}

const glm::vec3& UserInterface::getBackgroundColor() const noexcept {
    return backgroundColor;
}

const glm::vec3& UserInterface::getGridColor() const noexcept {
    return gridColor;
}
}