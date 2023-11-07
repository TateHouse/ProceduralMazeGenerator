#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

#include "Window.hpp"

namespace Renderer {
OrthographicCamera::OrthographicCamera(Context& context) noexcept: Component {context} {
}

void OrthographicCamera::initialize() {
    setZoomLevel(zoomLevel);
    viewProjection = projection * view;
}

void OrthographicCamera::postInitialize() {

}

void OrthographicCamera::update() {
    if (isDirty) {
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), position);
        const auto rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        const auto transform = rotationMatrix * translationMatrix;

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

void OrthographicCamera::setZoomLevel(const float zoomLevel) noexcept {
    this->zoomLevel = std::clamp(zoomLevel,
                                 OrthographicCameraDefaults::getMinZoomLevel(),
                                 OrthographicCameraDefaults::getMaxZoomLevel());

    const auto aspectRatio {Renderer::Window::getAspectRatio()};
    const auto updatedLeft {-aspectRatio / (this->zoomLevel * 2.0f)};
    const auto updatedRight {aspectRatio / (this->zoomLevel * 2.0f)};
    const auto updatedBottom {-1.0f / (this->zoomLevel * 2.0f)};
    const auto updatedTop {1.0f / (this->zoomLevel * 2.0f)};

    left = updatedLeft;
    right = updatedRight;
    bottom = updatedBottom;
    top = updatedTop;

    projection = glm::ortho(left, right, bottom, top, near, far);
    isDirty = true;
}
}