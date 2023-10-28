#pragma once

#include <memory>

#include "Context.hpp"
#include "OrthographicCamera.hpp"
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
    Context context;
    std::unique_ptr<OrthographicCamera> camera;
    std::unique_ptr<Window> window;
};
}