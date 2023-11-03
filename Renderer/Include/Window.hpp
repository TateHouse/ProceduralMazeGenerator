#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Component.hpp"

namespace Renderer {
class Window final : public Component {
public:
    explicit Window(Context& context) noexcept;
    ~Window() noexcept override = default;

public:
    virtual void initialize() override;
    virtual void postInitialize() override;
    virtual void update() override;
    virtual void postUpdate() override;
    virtual void render() override;
    virtual void postRender() override;
    virtual void destroy() override;

public:
    [[nodiscard]] const bool getIsKeyDown(const int key) const noexcept;
    [[nodiscard]] const bool getWindowShouldClose() const noexcept;
    void setWindowShouldClose() noexcept;
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

    [[nodiscard]] static constexpr int getWidth() noexcept {
        return width;
    }

    [[nodiscard]] static constexpr int getHeight() noexcept {
        return height;
    }

    [[nodiscard]] static constexpr float getAspectRatio() noexcept {
        return static_cast<float>(width) / static_cast<float>(height);
    }

private:
    GLFWwindow* window {nullptr};
    static constexpr int width {1280};
    static constexpr int height {720};
    const std::string title {"Maze Generator"};
};
}