#pragma once

#include <memory>

#include "Context.hpp"
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

    [[nodiscard]] const bool getIsRunning() const noexcept;

private:
    bool isRunning {true};
    Context context;
    std::unique_ptr<Window> window;
};
}