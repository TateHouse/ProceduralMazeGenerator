#pragma once

#include <glm/glm.hpp>

namespace Renderer {
class OrthographicCameraDefaults {
public:
    OrthographicCameraDefaults() = delete;

public:
    static const glm::vec3& getDefaultPosition() noexcept {
        return position;
    }

    static constexpr float getDefaultRotation() noexcept {
        return rotation;
    }

    static constexpr float getDefaultZoomLevel() noexcept {
        return zoomLevel;
    }

private:
    static constexpr glm::vec3 position {0.0f, 0.0f, 0.0f};
    static constexpr float rotation {0.0f};
    static constexpr float zoomLevel {1.0f};
};
}