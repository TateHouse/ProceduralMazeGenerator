#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace Renderer {
void Application::initialize() {
    window = std::make_unique<Window>(context);
    context.getWindowManager()->addWindow("Main", window.get());

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

    const auto left {-Renderer::Window::getAspectRatio()};
    const auto right {Renderer::Window::getAspectRatio()};
    const auto bottom {-1.0f};
    const auto top {1.0f};
    const auto near {-1.0f};
    const auto far {1.0f};
    camera = std::make_unique<OrthographicCamera>(context, left, right, bottom, top, near, far);
    camera->initialize();
}

void Application::postInitialize() {
    window->postInitialize();
    camera->postInitialize();
}

void Application::update() {
    context.update();
    window->update();
    camera->update();
}

void Application::postUpdate() {
    window->postUpdate();
    camera->postUpdate();

    glfwPollEvents();
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    camera->render();
    window->render();
}

void Application::postRender() {
    camera->postRender();
    window->postRender();
}

void Application::destroy() {
    window->destroy();
    camera->destroy();

    glfwTerminate();
}

const bool Application::getIsRunning() const noexcept {
    return isRunning && !window->getWindowShouldClose();
}
}
