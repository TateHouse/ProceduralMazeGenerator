#pragma once

#include <glad/glad.h>

#include <memory>
#include <utility>
#include <vector>

#include "Shader/ShaderProgram.hpp"
#include "Component.hpp"
#include "CellSettings.hpp"
#include "SquareGrid.hpp"

namespace Renderer {
class SquareMaze final : public Component {
public:
    SquareMaze(Context& context, const Core::SquareGrid* const grid, const CellSettings& cellSettings);
    virtual ~SquareMaze() noexcept override = default;

public:
    virtual void initialize() override;
    virtual void postInitialize() override;
    virtual void update() override;
    virtual void postUpdate() override;
    virtual void render() override;
    virtual void postRender() override;
    virtual void destroy() override;

private:
    void insertEastCellWallVertices(std::vector<float>& vertices,
                                    const std::pair<const float, const float>& coordinates) const;
    void insertSouthCellWallVertices(std::vector<float>& vertices,
                                     const std::pair<const float, const float>& coordinates) const;
    void insertNorthOuterWallVertices(std::vector<float>& vertices) const;
    void insertWestOuterWallVertices(std::vector<float>& vertices) const;
    void insertSouthOuterWallVertices(std::vector<float>& vertices) const;
    void insertEastOuterWallVertices(std::vector<float>& vertices) const;

private:
    const Core::SquareGrid* const grid;
    const CellSettings& cellSettings;
    std::pair<float, float> centerOffsets;
    std::size_t vertexCount {0};
    GLuint vao {0};
    GLuint vbo {0};
    std::unique_ptr<Shader::ShaderProgram> shaderProgram;
};
}