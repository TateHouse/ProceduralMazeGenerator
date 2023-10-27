#pragma once

#include <functional>

namespace Renderer::Utility {
class DeltaTimeCalculator final {
public:
    DeltaTimeCalculator(std::function<float()> timeSource) noexcept;

public:
    const float update() noexcept;
    [[nodiscard]] const float getDeltaTime() const noexcept;

private:
    std::function<float()> timeSource;
    float lastFrame {0.0f};
    float deltaTime {0.0f};
};
}