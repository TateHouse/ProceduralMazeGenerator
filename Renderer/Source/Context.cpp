#include "Context.hpp"

#include <GLFW/glfw3.h>

namespace Renderer {
Context::Context() noexcept {
    const auto timeFunction {[]() noexcept {
        return static_cast<float>(glfwGetTime());
    }};

    cameraManager = std::make_unique<Utility::CameraManager>();
    deltaTimeManager = std::make_unique<Utility::DeltaTimeManager>(timeFunction);
    windowManager = std::make_unique<Utility::WindowManager>();
}

void Context::update() noexcept {
    deltaTimeManager->update();
}

const bool Context::getIsRunning() const noexcept {
    return isRunning;
}

void Context::stopRunning() noexcept {
    isRunning = false;
}

Utility::CameraManager* const Context::getCameraManager() noexcept {
    return cameraManager.get();
}

Utility::DeltaTimeManager* const Context::getDeltaTimeManager() noexcept {
    return deltaTimeManager.get();
}

Utility::WindowManager* const Context::getWindowManager() noexcept {
    return windowManager.get();
}
}