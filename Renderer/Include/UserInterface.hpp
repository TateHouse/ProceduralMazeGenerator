#pragma once

#include <memory>
#include <vector>

#include "Component.hpp"
#include "CellSettings.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Renderer {
class UserInterface final : public Component {
public:
    UserInterface(Context& context,
                  CellSettings& cellSettings,
                  Core::SquareGrid& grid,
                  SquareMaze& squareMaze,
                  const std::vector<std::unique_ptr<Core::MazeGenerator>>& mazeGenerators);
    virtual ~UserInterface() noexcept = default;

public:
    virtual void initialize() override;
    virtual void postInitialize() override;
    virtual void update() override;
    virtual void postUpdate() override;
    virtual void render() override;
    virtual void postRender() override;
    virtual void destroy() override;

private:
    CellSettings& cellSettings;
    Core::SquareGrid& grid;
    SquareMaze& squareMaze;
    const std::vector<std::unique_ptr<Core::MazeGenerator>>& mazeGenerators;
    std::size_t selectedMazeGeneratorIndex {0};
};
}