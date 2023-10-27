#pragma once

#include <functional>

namespace Renderer::Utility {
class DeltaTimeCalculator final {
public:
    explicit DeltaTimeCalculator(const std::function<float()>& timeSource);

public:
    const float update() noexcept;
    [[nodiscard]] const float getDeltaTime() const noexcept;

private:
    const std::function<float()> timeSource;
    float lastFrame {0.0f};
    float deltaTime {0.0f};
};
}