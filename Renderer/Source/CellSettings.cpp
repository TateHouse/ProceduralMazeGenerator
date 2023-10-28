#include "CellSettings.hpp"

#include <algorithm>
#include <stdexcept>

namespace Renderer {
const float CellSettings::getSize() const noexcept {
    return size;
}

void CellSettings::setSize(const float size) {
    if (size <= 0.0f) {
        throw std::invalid_argument("Cell size must be positive");
    }

    this->size = size;
}

const float CellSettings::getWallThickness() const noexcept {
    return wallThickness;
}

void CellSettings::setWallThickness(const float wallThickness) noexcept {
    this->wallThickness = std::clamp(wallThickness, minimumWallThickness, maximumWallThickness);
}

const glm::vec3& CellSettings::getWallColor() const noexcept {
    return wallColor;
}

void CellSettings::setWallColor(const glm::vec3& wallColor) {
    for (auto index {0}; index < 2; ++index) {
        const auto element {wallColor[index]};

        if (element < 0.0f || element > 1.0f) {
            throw std::invalid_argument("Wall color must be in the range [0, 1]");
        }
    }

    this->wallColor = wallColor;
}
}