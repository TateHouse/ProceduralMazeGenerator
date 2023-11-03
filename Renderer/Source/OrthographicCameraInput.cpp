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
    const auto areMovementKeysPressed {std::array<bool, 6> {
            window->getIsKeyDown(GLFW_KEY_W),
            window->getIsKeyDown(GLFW_KEY_S),
            window->getIsKeyDown(GLFW_KEY_A),
            window->getIsKeyDown(GLFW_KEY_D),
            window->getIsKeyDown(GLFW_KEY_Q),
            window->getIsKeyDown(GLFW_KEY_E)
    }};

    const auto isAnyMovementKeyPressed {
            std::any_of(areMovementKeysPressed.begin(), areMovementKeysPressed.end(), [](const bool isPressed) {
                return isPressed;
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
    glm::vec3 moveDirection {};
    float updatedRotation {};

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
    camera->setPosition(nextPosition);

    if (window->getIsKeyDown(GLFW_KEY_Q)) {
        updatedRotation = updatedRotation - rotationSpeed;
    } else if (window->getIsKeyDown(GLFW_KEY_E)) {
        updatedRotation = updatedRotation + rotationSpeed;
    }

    const auto nextRotation {currentRotation + updatedRotation};
    camera->setRotation(nextRotation);
}
}