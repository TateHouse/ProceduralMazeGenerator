#include "MazeRenderer.hpp"

#include <stdexcept>
#include <vector>

#include "Utility/UnitScale.hpp"

namespace Renderer {
MazeRenderer::MazeRenderer(const Core::Grid* const grid, const float cellSize) : grid {grid}, cellSize {cellSize} {
    if (grid == nullptr) {
        throw std::invalid_argument {"grid cannot be null"};
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    const auto [gridWidth, gridHeight] {grid->getSize()};
    updateVertices();
    shader = std::make_unique<Shader>("Shaders/Test.vert", "Shaders/Test.frag", "Shaders/Test.geom");
}

MazeRenderer::~MazeRenderer() noexcept {
    destroy();
}

void MazeRenderer::updateVertices() {
    const auto [gridWidth, gridHeight] {grid->getSize()};
    halfWidth = static_cast<float>(gridWidth) * cellSize * 0.5f;
    halfHeight = static_cast<float>(gridHeight) * cellSize * 0.5f;

    std::vector<float> vertices {};
    const auto cellCount {gridWidth * gridHeight};
    vertices.reserve(cellCount * 3);

    for (auto row {gridHeight - 1}; row >= 0; --row) {
        for (auto column {0}; column < gridWidth; ++column) {
            const auto xGridPosition {column};
            const auto yGridPosition {static_cast<int>(row)};
            const auto* const cell {(*grid)[{xGridPosition, yGridPosition}]};

            const auto xCoordinate {(static_cast<float>(xGridPosition) * cellSize) - halfWidth};
            const auto yCoordinate {(static_cast<float>(yGridPosition) * cellSize) - halfHeight};

            const auto* const eastNeighbor {cell->getEast()};
            const auto* const southNeighbor {cell->getSouth()};

            if (!cell->isLinked(eastNeighbor) && column != gridWidth - 1) {
                vertices.push_back(xCoordinate + cellSize);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);

                vertices.push_back(xCoordinate + cellSize);
                vertices.push_back(yCoordinate + cellSize);
                vertices.push_back(0.0f);
            }

            if (!cell->isLinked(southNeighbor) && row != 0) {
                vertices.push_back(xCoordinate);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);

                vertices.push_back(xCoordinate + cellSize);
                vertices.push_back(yCoordinate);
                vertices.push_back(0.0f);
            }
        }
    }

    insertNorthWallVertices(vertices);
    insertWestWallVertices(vertices);
    insertSouthWallVertices(vertices);
    insertEastWallVertices(vertices);

    vertexCount = vertices.size() / 3;

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MazeRenderer::update(const float deltaTime,
                          const float cellSize,
                          const float lineThickness,
                          const float aspectRatio,
                          const glm::vec3& color) {
    this->cellSize = cellSize;
    this->lineThickness = lineThickness;
    this->aspectRatio = aspectRatio;
    this->color = color;
}

void MazeRenderer::render(const glm::mat4& projectionMatrix) {
    shader->use();
    shader->setUniformMatrix4x4fv("projection", projectionMatrix);
    shader->setUniform1f("lineThickness", lineThickness);
    shader->setUniform1f("aspectRatio", aspectRatio);
    shader->setUniform3fv("color", color);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertexCount));
    glBindVertexArray(0);
}

void MazeRenderer::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void MazeRenderer::insertNorthWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}

void MazeRenderer::insertWestWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(-halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}

void MazeRenderer::insertSouthWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(-halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
}

void MazeRenderer::insertEastWallVertices(std::vector<float>& vertices) const {
    vertices.push_back(halfWidth);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(halfWidth);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
}
}