#include "Utility/DeltaTimeCalculator.hpp"

#include <stdexcept>

namespace Renderer::Utility {
DeltaTimeCalculator::DeltaTimeCalculator(const std::function<float()>& timeSource) : timeSource {timeSource} {
    if (timeSource == nullptr) {
        throw std::invalid_argument {"The time source function must be specified."};
    }
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