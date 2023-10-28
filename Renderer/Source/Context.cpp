#include "Context.hpp"

#include <GLFW/glfw3.h>

namespace Renderer {
Context::Context() noexcept {
    const auto timeFunction {[]() noexcept {
        return static_cast<float>(glfwGetTime());
    }};

    deltaTimeManager = std::make_unique<Utility::DeltaTimeManager>(timeFunction);
    windowManager = std::make_unique<Utility::WindowManager>();
}

void Context::update() noexcept {
    deltaTimeManager->update();
}

Utility::DeltaTimeManager* const Context::getDeltaTimeManager() noexcept {
    return deltaTimeManager.get();
}

Utility::WindowManager* const Context::getWindowManager() noexcept {
    return windowManager.get();
}
}