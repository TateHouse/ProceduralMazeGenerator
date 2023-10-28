#include "Maze.hpp"

#include "OrthographicCamera.hpp"
#include "Window.hpp"

#include <iostream>
#include <stdexcept>

namespace Renderer {
SquareMaze::SquareMaze(Context& context, const Core::SquareGrid* const grid, const CellSettings& cellSettings)
        : Component {context}, grid {grid}, cellSettings {cellSettings} {
    if (grid == nullptr) {
        throw std::invalid_argument {"SquareMaze::SquareMaze: grid cannot be nullptr."};
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

void SquareMaze::initialize() {
    const auto [gridWidth, gridHeight] = grid->getSize();
    const auto centerHorizontalOffset {static_cast<float>(gridWidth) * cellSettings.getSize() * 0.5f};
    const auto centerVerticalOffset {static_cast<float>(gridHeight) * cellSettings.getSize() * 0.5f};
    centerOffsets = {centerHorizontalOffset, centerVerticalOffset};

    std::vector<float> vertices {};
    const auto cellCount {gridWidth * gridHeight};
    vertices.reserve(cellCount * 3);

    for (auto row {gridHeight - 1}; row >= 0; --row) {
        for (auto column {0}; column < gridWidth; ++column) {
            const auto* const cell {(*grid)[{column, row}]};
            const auto xCoordinate {(static_cast<float>(column) * cellSettings.getSize()) - centerHorizontalOffset};
            const auto yCoordinate {(static_cast<float>(row) * cellSettings.getSize()) - centerVerticalOffset};
            const auto coordinates {std::make_pair(xCoordinate, yCoordinate)};

            if (const auto* const eastCell {cell->getEast()}; column != gridWidth - 1 && !cell->isLinked(eastCell)) {
                insertEastCellWallVertices(vertices, coordinates);
            }

            if (const auto* const southCell {cell->getSouth()}; row != 0 && !cell->isLinked(southCell)) {
                insertSouthCellWallVertices(vertices, coordinates);
            }
        }
    }

    insertNorthOuterWallVertices(vertices);
    insertWestOuterWallVertices(vertices);
    insertSouthOuterWallVertices(vertices);
    insertEastOuterWallVertices(vertices);

    vertexCount = vertices.size() / 3;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SquareMaze::postInitialize() {
    auto vertexShader {Renderer::Shader::VertexShader {"Shaders/Maze.vert"}};
    auto fragmentShader {Renderer::Shader::FragmentShader {"Shaders/Maze.frag"}};
    shaderProgram = std::make_unique<Shader::ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));
    shaderProgram->link();
}

void SquareMaze::update() {

}

void SquareMaze::postUpdate() {

}

void SquareMaze::render() {
    shaderProgram->use();
    shaderProgram->setUniformMatrix4x4fv("projection", context.getCameraManager()->getCamera("Main")->getProjection());
    shaderProgram->setUniformMatrix4x4fv("view", context.getCameraManager()->getCamera("Main")->getView());
    shaderProgram->setUniformMatrix4x4fv("model", glm::mat4 {1.0f});

    shaderProgram->setUniform3fv("wallColor", cellSettings.getWallColor());

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertexCount);
    glBindVertexArray(0);
}

void SquareMaze::postRender() {

}

void SquareMaze::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void SquareMaze::insertEastCellWallVertices(std::vector<float>& vertices,
                                            const std::pair<const float, const float>& coordinates) const {
    vertices.push_back(coordinates.first + cellSettings.getSize());
    vertices.push_back(coordinates.second);
    vertices.push_back(0.0f);

    vertices.push_back(coordinates.first + cellSettings.getSize());
    vertices.push_back(coordinates.second + cellSettings.getSize());
    vertices.push_back(0.0f);
}

void SquareMaze::insertSouthCellWallVertices(std::vector<float>& vertices,
                                             const std::pair<const float, const float>& coordinates) const {
    vertices.push_back(coordinates.first);
    vertices.push_back(coordinates.second);
    vertices.push_back(0.0f);

    vertices.push_back(coordinates.first + cellSettings.getSize());
    vertices.push_back(coordinates.second);
    vertices.push_back(0.0f);
}

void SquareMaze::insertNorthOuterWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-centerOffsets.first);
    vertices.push_back(centerOffsets.second);
    vertices.push_back(0.0f);

    vertices.push_back(centerOffsets.first);
    vertices.push_back(centerOffsets.second);
    vertices.push_back(0.0f);
}

void SquareMaze::insertWestOuterWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-centerOffsets.first);
    vertices.push_back(-centerOffsets.second);
    vertices.push_back(0.0f);

    vertices.push_back(-centerOffsets.first);
    vertices.push_back(centerOffsets.second);
    vertices.push_back(0.0f);
}

void SquareMaze::insertSouthOuterWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-centerOffsets.first);
    vertices.push_back(-centerOffsets.second);
    vertices.push_back(0.0f);

    vertices.push_back(centerOffsets.first);
    vertices.push_back(-centerOffsets.second);
    vertices.push_back(0.0f);
}

void SquareMaze::insertEastOuterWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(centerOffsets.first);
    vertices.push_back(-centerOffsets.second);
    vertices.push_back(0.0f);

    vertices.push_back(centerOffsets.first);
    vertices.push_back(centerOffsets.second);
    vertices.push_back(0.0f);
}
}