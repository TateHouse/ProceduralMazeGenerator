#include "Utility/DeltaTimeManager.hpp"

#include <stdexcept>

namespace Renderer::Utility {
DeltaTimeManager::DeltaTimeManager(const std::function<float()>& timeFunction) : timeFunction {timeFunction} {
    if (timeFunction == nullptr) {
        // TODO: Throw custom exception.
        throw std::runtime_error {"The time function cannot be null."};
    }
}

void DeltaTimeManager::update() noexcept {
    currentFrameTime = timeFunction();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
    elapsedTime = elapsedTime + deltaTime;
    framesPerSecond = 1.0f / deltaTime;
}

const float DeltaTimeManager::getElapsedTime() const noexcept {
    return elapsedTime;
}

const float DeltaTimeManager::getCurrentFrameTime() const noexcept {
    return currentFrameTime;
}

const float DeltaTimeManager::getLastFrameTime() const noexcept {
    return lastFrameTime;
}

const float DeltaTimeManager::getDeltaTime() const noexcept {
    return deltaTime;
}

float DeltaTimeManager::getFixedDeltaTime() noexcept {
    return fixedDeltaTime;
}

const float DeltaTimeManager::getFramesPerSecond() const noexcept {
    return framesPerSecond;
}
}