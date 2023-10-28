#pragma once

#include <imgui.h>

#include <array>
#include <memory>

#include "MazeGenerator.hpp"
#include "MazeRenderer.hpp"
#include "SquareGrid.hpp"
#include "Window.hpp"

namespace Renderer {
class UserInterface final {
public:
    UserInterface(const std::array<std::unique_ptr<Core::MazeGenerator>, 2>& mazeGenerators,
                  MazeRenderer* const mazeRenderer,
                  Core::Grid* const grid,
                  const Window& window) noexcept;
    ~UserInterface() noexcept;

public:
    void initialize();
    void update(const float currentFrame);
    void render() const;
    void destroy();

    [[nodiscard]] const glm::vec3& getBackgroundColor() const noexcept;
    [[nodiscard]] const glm::vec3& getGridColor() const noexcept;

private:
    ImGuiContext* context {nullptr};
    ImGuiIO* io {nullptr};
    const std::array<std::unique_ptr<Core::MazeGenerator>, 2>& mazeGenerators;
    MazeRenderer* const mazeRenderer;
    Core::Grid* const grid {nullptr};
    const Window& window;
    std::size_t selectedMazeGeneratorIndex {0};
    glm::vec3 backgroundColor {0.0f, 0.0f, 0.0f};
    glm::vec3 gridColor {1.0f, 1.0f, 1.0f};
};
}