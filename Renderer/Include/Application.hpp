#pragma once

#include <memory>

#include "CellSettings.hpp"
#include "Context.hpp"
#include "Maze.hpp"
#include "OrthographicCamera.hpp"
#include "SquareGrid.hpp"
#include "Window.hpp"

namespace Renderer {
class Application final {
public:
    Application() noexcept = default;

public:
    void initialize();
    void postInitialize();
    void update();
    void postUpdate();
    void render();
    void postRender();
    void destroy();

public:
    [[nodiscard]] const bool getIsRunning() const noexcept;

private:
    Context context;
    std::unique_ptr<SquareMaze> squareMaze;
    std::unique_ptr<OrthographicCamera> camera;
    std::unique_ptr<Window> window;
    std::unique_ptr<Core::SquareGrid> grid;
    CellSettings cellSettings {};

};
}