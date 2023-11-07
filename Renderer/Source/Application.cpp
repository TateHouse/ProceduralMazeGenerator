#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "BinaryTreeMazeGenerator.hpp"
#include "OrthographicCameraInput.hpp"
#include "SidewinderMazeGenerator.hpp"
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

    mazeGenerators = std::vector<std::unique_ptr<Core::MazeGenerator>> {};
    mazeGenerators.emplace_back(std::make_unique<Core::BinaryTreeMazeGenerator>());
    mazeGenerators.emplace_back(std::make_unique<Core::SidewinderMazeGenerator>());

    userInterface = std::make_unique<UserInterface>(context, cellSettings, *grid, *squareMaze, mazeGenerators);
    userInterface->initialize();

    inputComponents = std::vector<std::unique_ptr<InputComponent>> {};
    inputComponents.emplace_back(std::make_unique<OrthographicCameraInput>(context));
}

void Application::postInitialize() {
    window->postInitialize();
    camera->postInitialize();
    userInterface->postInitialize();
    squareMaze->postInitialize();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->initialize();
    }
}

void Application::update() {
    context.update();
    window->update();
    camera->update();
    userInterface->update();
    squareMaze->update();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->update();
    }
}

void Application::postUpdate() {
    window->postUpdate();
    userInterface->postUpdate();
    camera->postUpdate();
    squareMaze->postUpdate();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->postUpdate();
    }

    glfwPollEvents();
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const auto backgroundColor {cellSettings.getBackgroundColor()};
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);

    squareMaze->render();
    camera->render();
    userInterface->render();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->render();
    }

    window->render();
}

void Application::postRender() {
    squareMaze->postRender();
    camera->postRender();
    userInterface->postRender();
    window->postRender();

    for (const auto& inputComponent : inputComponents) {
        inputComponent->postRender();
    }
}

void Application::destroy() {
    window->destroy();
    camera->destroy();
    userInterface->destroy();
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
