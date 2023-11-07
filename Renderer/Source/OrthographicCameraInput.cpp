#include "OrthographicCameraInput.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>

#include "OrthographicCamera.hpp"
#include "Window.hpp"

namespace Renderer {
void OrthographicCameraInput::initialize() {

}

void OrthographicCameraInput::postInitialize() {

}

void OrthographicCameraInput::update() {
    const auto* window {context.getWindowManager()->getWindow("Main")};
    const auto areMovementKeysPressed {std::array<bool, 9> {
            window->getIsKeyDown(GLFW_KEY_W),
            window->getIsKeyDown(GLFW_KEY_S),
            window->getIsKeyDown(GLFW_KEY_A),
            window->getIsKeyDown(GLFW_KEY_D),
            window->getIsKeyDown(GLFW_KEY_Q),
            window->getIsKeyDown(GLFW_KEY_E),
            window->getIsKeyDown(GLFW_KEY_R),
            window->getIsKeyDown(GLFW_KEY_Z),
            window->getIsKeyDown(GLFW_KEY_C)

    }};

    const auto isAnyMovementKeyPressed {
            std::ranges::any_of(areMovementKeysPressed, [](const bool isKeyPressed) {
                return isKeyPressed;
            })};

    if (isAnyMovementKeyPressed) {
        onKeyDown();
    }
}

void OrthographicCameraInput::postUpdate() {

}

void OrthographicCameraInput::render() {

}

void OrthographicCameraInput::postRender() {

}

void OrthographicCameraInput::destroy() {

}

void OrthographicCameraInput::onKeyDown() {
    const auto* window {context.getWindowManager()->getWindow("Main")};
    auto* camera {context.getCameraManager()->getCamera("Main")};
    const auto currentPosition {camera->getPosition()};
    const auto currentRotation {camera->getRotation()};
    const auto currentZoomLevel {camera->getZoomLevel()};
    glm::vec3 moveDirection {};
    float updatedRotation {};
    float updatedZoomLevel {};

    if (window->getIsKeyDown(GLFW_KEY_R)) {
        camera->setPosition(OrthographicCameraDefaults::getDefaultPosition());
        camera->setRotation(OrthographicCameraDefaults::getDefaultRotation());
        camera->setZoomLevel(OrthographicCameraDefaults::getDefaultZoomLevel());
        return;
    }

    if (window->getIsKeyDown(GLFW_KEY_W)) {
        moveDirection = moveDirection + glm::vec3 {0.0f, moveSpeed, 0.0f};
    } else if (window->getIsKeyDown(GLFW_KEY_S)) {
        moveDirection = moveDirection + glm::vec3 {0.0f, -moveSpeed, 0.0f};
    }

    if (window->getIsKeyDown(GLFW_KEY_D)) {
        moveDirection = moveDirection + glm::vec3 {moveSpeed, 0.0f, 0.0f};
    } else if (window->getIsKeyDown(GLFW_KEY_A)) {
        moveDirection = moveDirection + glm::vec3 {-moveSpeed, 0.0f, 0.0f};
    }

    const auto nextPosition {currentPosition + moveDirection};
    if (nextPosition != currentPosition) {
        camera->setPosition(nextPosition);
    }

    if (window->getIsKeyDown(GLFW_KEY_Q)) {
        updatedRotation = updatedRotation - rotationSpeed;
    } else if (window->getIsKeyDown(GLFW_KEY_E)) {
        updatedRotation = updatedRotation + rotationSpeed;
    }

    const auto nextRotation {currentRotation + updatedRotation};
    if (nextRotation != 0) {
        camera->setRotation(nextRotation);
    }

    if (window->getIsKeyDown(GLFW_KEY_Z)) {
        updatedZoomLevel = -zoomSpeed;

    } else if (window->getIsKeyDown(GLFW_KEY_C)) {
        updatedZoomLevel = zoomSpeed;
    }

    const auto nextZoomLevel {currentZoomLevel + updatedZoomLevel};
    if (nextZoomLevel != currentZoomLevel) {
        camera->setZoomLevel(nextZoomLevel);
    }
}
}