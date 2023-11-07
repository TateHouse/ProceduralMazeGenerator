#pragma once

#include <glm/glm.hpp>

#include "Utility/UnitScale.hpp"

namespace Renderer {
class CellSettings final {
public:
    [[nodiscard]] const float getSize() const noexcept;
    void setSize(const float size);
    [[nodiscard]] const float getWallThickness() const noexcept;
    void setWallThickness(const float wallThickness) noexcept;
    [[nodiscard]] const glm::vec3& getWallColor() const noexcept;
    void setWallColor(const glm::vec3& wallColor);
    [[nodiscard]] const glm::vec3& getBackgroundColor() const noexcept;
    void setBackgroundColor(const glm::vec3& backgroundColor);

private:
    float size {7.5f * Utility::unitScale};
    float wallThickness {minimumWallThickness};
    static constexpr float minimumWallThickness {0.002f};
    static constexpr float maximumWallThickness {0.03f};
    glm::vec3 wallColor {1.0f, 1.0f, 1.0f};
    glm::vec3 backgroundColor {0.0f, 0.0f, 0.0f};
};
}