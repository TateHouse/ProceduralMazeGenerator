#include "Utility/DeltaTimeCalculator.hpp"

namespace Renderer::Utility {
DeltaTimeCalculator::DeltaTimeCalculator(std::function<float()> timeSource) noexcept: timeSource {timeSource} {

}

const float DeltaTimeCalculator::update() noexcept {
    const auto currentFrame {timeSource()};
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return currentFrame;
}

const float DeltaTimeCalculator::getDeltaTime() const noexcept {
    return deltaTime;
}
}