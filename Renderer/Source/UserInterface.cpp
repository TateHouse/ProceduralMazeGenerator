#include "UserInterface.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Renderer {
UserInterface::UserInterface(Context& context,
                             CellSettings& cellSettings,
                             Core::SquareGrid& grid,
                             SquareMaze& squareMaze,
                             const std::vector<std::unique_ptr<Core::MazeGenerator>>& mazeGenerators) :
        Component {context},
        cellSettings {cellSettings},
        grid {grid},
        squareMaze {squareMaze},
        mazeGenerators {mazeGenerators} {

}

void UserInterface::initialize() {

}

void UserInterface::postInitialize() {

}

void UserInterface::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Maze Generator");

    if (ImGui::Button("Generate Maze")) {
        grid.reset();
        mazeGenerators[selectedMazeGeneratorIndex]->generate(&grid, nullptr);
        squareMaze.initialize();
    }

    if (ImGui::Button("Generate Grid")) {
        grid.reset();
        grid.initialize();
        squareMaze.initialize();
    }

    auto generatorName {mazeGenerators[selectedMazeGeneratorIndex]->getAlgorithmName()};
    if (ImGui::BeginCombo("Maze Generator", generatorName.c_str())) {
        for (std::size_t index {0}; index < mazeGenerators.size(); ++index) {
            auto isSelected {selectedMazeGeneratorIndex == index};

            generatorName = mazeGenerators[index]->getAlgorithmName();
            if (ImGui::Selectable(generatorName.c_str(), isSelected)) {
                selectedMazeGeneratorIndex = index;
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    try {
        auto cellSize {cellSettings.getSize()};
        auto cellWallThickness {cellSettings.getWallThickness()};
        auto cellWallColor {cellSettings.getWallColor()};
        auto backgroundColor {cellSettings.getBackgroundColor()};

        ImGui::InputFloat("Cell Size", &cellSize);
        ImGui::InputFloat("Cell Wall Thickness", &cellWallThickness);
        ImGui::ColorEdit3("Cell Wall Color", glm::value_ptr(cellWallColor));
        ImGui::ColorEdit3("Background Color", glm::value_ptr(backgroundColor));

        cellSettings.setSize(cellSize);
        cellSettings.setWallThickness(cellWallThickness);
        cellSettings.setWallColor(cellWallColor);
        cellSettings.setBackgroundColor(backgroundColor);
    } catch (const std::invalid_argument& exception) {
        ImGui::Text(exception.what());
    }

    ImGui::End();
}

void UserInterface::postUpdate() {

}

void UserInterface::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::postRender() {

}

void UserInterface::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

}