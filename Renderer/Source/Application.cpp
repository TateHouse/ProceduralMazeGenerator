#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "OrthographicCameraInput.hpp"
#include "SquareGrid.hpp"

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

    camera = std::make_unique<OrthographicCamera>(context);
    context.getCameraManager()->addCamera("Main", camera.get());
    camera->initialize();

    grid = std::make_unique<Core::SquareGrid>(20);
    grid->initialize();
    squareMaze = std::make_unique<SquareMaze>(context, grid.get(), cellSettings);
    squareMaze->initialize();

    inputComponents = std::vector<std::unique_ptr<InputComponent>> {};
    inputComponents.emplace_back(std::make_unique<OrthographicCameraInput>(context));
}

void Application::postInitialize() {
    window->postInitialize();
    camera->postInitialize();
    squareMaze->postInitialize();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->initialize();
    }
}

void Application::update() {
    context.update();
    window->update();
    camera->update();
    squareMaze->update();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->update();
    }
}

void Application::postUpdate() {
    window->postUpdate();
    camera->postUpdate();
    squareMaze->postUpdate();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->postUpdate();
    }

    glfwPollEvents();
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    squareMaze->render();
    camera->render();
    window->render();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->render();
    }
}

void Application::postRender() {
    squareMaze->postRender();
    camera->postRender();
    window->postRender();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->postRender();
    }
}

void Application::destroy() {
    window->destroy();
    camera->destroy();
    squareMaze->destroy();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->destroy();
    }

    glfwTerminate();
}

const bool Application::getIsRunning() const noexcept {
    return context.getIsRunning() && !window->getWindowShouldClose();
}
}
