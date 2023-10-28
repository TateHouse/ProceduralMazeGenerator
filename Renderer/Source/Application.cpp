#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace Renderer {
void Application::initialize() {
    window = std::make_unique<Window>(context);

    if (!glfwInit()) {
        // TODO: Log error.
        // TODO: Throw custom exception.
        throw std::runtime_error {"Failed to initialize GLFW."};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->initialize();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        // TODO: Log error.
        // TODO: Throw custom exception.
        throw std::runtime_error {"Failed to initialize GLAD."};
    }
}

void Application::postInitialize() {
    window->postInitialize();
}

void Application::update() {
    context.update();
    window->update();
}

void Application::postUpdate() {
    window->postUpdate();

    glfwPollEvents();
}

void Application::render() {
    window->render();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Application::postRender() {
    window->postRender();
}

void Application::destroy() {
    window->destroy();

    glfwTerminate();
}

const bool Application::getIsRunning() const noexcept {
    return isRunning && !window->getWindowShouldClose();
}
}
