#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>

namespace Renderer {
class Window final {
public:
    Window(const unsigned int width, const unsigned int height, const std::string_view title);
    ~Window() noexcept;

public:
    const bool initialize() noexcept;
    const bool initializeImGui() noexcept;
    void update(const float deltaTime) noexcept;
    void render() noexcept;
    void close() noexcept;

    const unsigned int getWidth() const noexcept;
    const unsigned int getHeight() const noexcept;
    const bool getShouldClose() const noexcept;
    void setShouldClose(const bool shouldClose) noexcept;
    void setCallbacks() noexcept;

public:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    GLFWwindow* window {nullptr};
    unsigned int width;
    unsigned int height;
    std::string title;
};
}