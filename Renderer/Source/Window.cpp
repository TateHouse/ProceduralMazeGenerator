#include "Window.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <format>
#include <stdexcept>

namespace Renderer {
Window::Window(Context& context) noexcept: Component {context} {

}

void Window::initialize() {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        // TODO: Log error.
        // TODO: Throw custom exception.
        throw std::runtime_error {"Failed to create GLFW window."};
    }

    glfwMakeContextCurrent(window);
}

void Window::postInitialize() {
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto& io {ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

void Window::update() {
    const auto framesPerSecond {context.getDeltaTimeManager()->getFramesPerSecond()};
    const auto updatedTitle {std::format("{} - FPS: {:.2f}", title, framesPerSecond)};
    glfwSetWindowTitle(window, updatedTitle.c_str());
}

void Window::postUpdate() {

}

void Window::render() {
    glfwSwapBuffers(window);
}

void Window::postRender() {

}

void Window::destroy() {
    glfwDestroyWindow(window);
    window = nullptr;
}

const bool Window::getIsKeyDown(const int key) const noexcept {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

const bool Window::getWindowShouldClose() const noexcept {
    return glfwWindowShouldClose(window);
}

void Window::setWindowShouldClose() noexcept {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept {
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
    auto* const currentWindow {static_cast<Window*>(glfwGetWindowUserPointer(window))};

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
}