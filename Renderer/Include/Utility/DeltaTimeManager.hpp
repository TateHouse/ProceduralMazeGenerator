#pragma once

#include <functional>

namespace Renderer::Utility {
class DeltaTimeManager final {
public:
    explicit DeltaTimeManager(const std::function<float()>& timeFunction);

public:
    void update() noexcept;

    [[nodiscard]] const float getElapsedTime() const noexcept;
    [[nodiscard]] const float getCurrentFrameTime() const noexcept;
    [[nodiscard]] const float getLastFrameTime() const noexcept;
    [[nodiscard]] const float getDeltaTime() const noexcept;
    [[nodiscard]] static float getFixedDeltaTime() noexcept;
    [[nodiscard]] const float getFramesPerSecond() const noexcept;

private:
    const std::function<float()> timeFunction;
    float elapsedTime {0.0f};
    float currentFrameTime {0.0f};
    float lastFrameTime {0.0f};
    float deltaTime {0.0f};
    static constexpr float fixedDeltaTime {1.0f / 60.0f};
    float framesPerSecond {0.0f};
};
}