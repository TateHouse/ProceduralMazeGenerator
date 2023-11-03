#include "OrthographicCameraInput.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OrthographicCamera.hpp"
#include "Window.hpp"

namespace Renderer {
void OrthographicCameraInput::initialize() {

}

void OrthographicCameraInput::postInitialize() {

}

void OrthographicCameraInput::update() {
    const auto* window {context.getWindowManager()->getWindow("Main")};

    const auto isForwardKeyDown {window->getIsKeyDown(GLFW_KEY_W)};
    const auto isBackwardKeyDown {window->getIsKeyDown(GLFW_KEY_S)};
    const auto isLeftKeyDown {window->getIsKeyDown(GLFW_KEY_A)};
    const auto isRightKeyDown {window->getIsKeyDown(GLFW_KEY_D)};

    if (isForwardKeyDown || isBackwardKeyDown || isLeftKeyDown || isRightKeyDown) {
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
    glm::vec3 moveDirection {};

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
}
}