#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

#include "Shader.hpp"
#include "SquareGrid.hpp"

namespace Renderer {
class MazeRenderer final {
public:
    explicit MazeRenderer(const Core::Grid* const grid, const float cellSize);
    ~MazeRenderer() noexcept;

public:
    void updateVertices();
    void update(const float deltaTime,
                const float cellSize,
                const float lineThickness,
                const float aspectRatio,
                const glm::vec3& color);
    void render(const glm::mat4& projectionMatrix);
    void destroy();

private:
    void insertNorthWallVertices(std::vector<float>& vertices) const;
    void insertWestWallVertices(std::vector<float>& vertices) const;
    void insertSouthWallVertices(std::vector<float>& vertices) const;
    void insertEastWallVertices(std::vector<float>& vertices) const;

private:
    const Core::Grid* const grid;
    float cellSize;
    float lineThickness;
    float aspectRatio;
    glm::vec3 color;
    float halfWidth;
    float halfHeight;
    std::size_t vertexCount {0};
    GLuint vao {0};
    GLuint vbo {0};
    std::unique_ptr<Shader> shader {nullptr};
};
}