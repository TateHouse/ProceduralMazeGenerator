#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

#include "Window.hpp"

namespace Renderer {
OrthographicCamera::OrthographicCamera(Context& context,
                                       const float left,
                                       const float right,
                                       const float bottom,
                                       const float top,
                                       const float near,
                                       const float far) noexcept:
        Component {context},
        left {left},
        right {right},
        bottom {bottom},
        top {top},
        near {near},
        far {far} {
}

void OrthographicCamera::initialize() {
    projection = glm::ortho(left, right, bottom, top, near, far);
    viewProjection = projection * view;
    isDirty = true;
}

void OrthographicCamera::postInitialize() {

}

void OrthographicCamera::update() {
    if (isDirty) {
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), position);
        const auto rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        const auto transform = translationMatrix * rotationMatrix;

        view = glm::inverse(transform);
        viewProjection = projection * view;
        isDirty = false;
    }
}

void OrthographicCamera::postUpdate() {

}

void OrthographicCamera::render() {

}

void OrthographicCamera::postRender() {

}

void OrthographicCamera::destroy() {

}

const glm::mat4& OrthographicCamera::getProjection() const noexcept {
    return projection;
}

const glm::mat4& OrthographicCamera::getView() const noexcept {
    return view;
}

const glm::mat4& OrthographicCamera::getViewProjection() const noexcept {
    return viewProjection;
}

const glm::vec3& OrthographicCamera::getPosition() const noexcept {
    return position;
}

void OrthographicCamera::setPosition(const glm::vec3& position) noexcept {
    this->position = position;
    isDirty = true;
}

const float OrthographicCamera::getRotation() const noexcept {
    return rotation;
}

void OrthographicCamera::setRotation(const float rotation) noexcept {
    this->rotation = std::fmod(rotation, 360.0f);
    isDirty = true;
}

const float OrthographicCamera::getZoomLevel() const noexcept {
    return zoomLevel;
}

void OrthographicCamera::setZoomLevel(const float zoomLevel, const float zoomSpeed) noexcept {
    static constexpr auto minZoomLevel {-10.0f};
    static constexpr auto maxZoomLevel {10.0f};

    this->zoomLevel = std::clamp(zoomLevel, minZoomLevel, maxZoomLevel);
    const auto zoomFactor = std::pow(zoomSpeed, this->zoomLevel);
    const auto aspectRatio {Renderer::Window::getAspectRatio()};
    const auto halfWidth {(right - left) / 2.0f / zoomFactor};
    const auto halfHeight {(top - bottom) / 2.0f / zoomFactor};

    const auto updatedLeft {-halfWidth * aspectRatio};
    const auto updatedRight {halfWidth * aspectRatio};
    const auto updatedBottom {-halfHeight};
    const auto updatedTop {halfHeight};

    projection = glm::ortho(updatedLeft, updatedRight, updatedBottom, updatedTop, near, far);
    isDirty = true;
}
}