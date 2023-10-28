#include "Window.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <format>
#include <stdexcept>

namespace Renderer {

Window::Window(const unsigned int width, const unsigned int height, const std::string_view title) :
        width {width}, height {height}, title {title.data()} {
    if (width < 800 || height < 600) {
        throw std::invalid_argument {"The minimum window size is 800x600."};
    }

    if (title.empty()) {
        throw std::invalid_argument {"The window title cannot be empty."};
    }
}

Window::~Window() noexcept {
    destroy();
}

const bool Window::initialize() noexcept {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }

    glfwMakeContextCurrent(window);

    return true;
}

const bool Window::initializeImGui() noexcept {
    if (window == nullptr) {
        return false;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    return true;
}

void Window::update(const float deltaTime) noexcept {
    const auto fps {1.0f / deltaTime};
    const auto formattedTitle {std::format("{} - FPS: {:.2f}", title, fps)};
    glfwSetWindowTitle(window, (formattedTitle).c_str());
}

void Window::render() noexcept {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::destroy() noexcept {
    if (window == nullptr) {
        return;
    }

    glfwDestroyWindow(window);
    window = nullptr;
}

const unsigned int Window::getWidth() const noexcept {
    return width;
}

const unsigned int Window::getHeight() const noexcept {
    return height;
}

const bool Window::getShouldClose() const noexcept {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(const bool shouldClose) noexcept {
    glfwSetWindowShouldClose(window, shouldClose);
}

void Window::setCallbacks() noexcept {
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto* const currentWindow {static_cast<Window*>(glfwGetWindowUserPointer(window))};
    currentWindow->width = width;
    currentWindow->height = height;

    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* const currentWindow {static_cast<Window*>(glfwGetWindowUserPointer(window))};

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(currentWindow->window, GLFW_TRUE);
    }
}
}