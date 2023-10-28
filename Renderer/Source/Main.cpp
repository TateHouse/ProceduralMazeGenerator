#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <iostream>

#include "Utility/DeltaTimeCalculator.hpp"
#include "Utility/UnitScale.hpp"
#include "BinaryTreeMazeGenerator.hpp"
#include "MazeRenderer.hpp"
#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"
#include "UserInterface.hpp"
#include "Window.hpp"

static constexpr auto WINDOW_WIDTH {1280};
static constexpr auto WINDOW_HEIGHT {720};
static constexpr auto WINDOW_TITLE {"Procedural Maze Generator Renderer"};
static constexpr auto SQUARE_GRID_SIZE {20};

glm::mat4 createOrthographicProjection(const float width,
                                       const float height,
                                       const float near,
                                       const float far) noexcept {
    const auto left {-width * 0.5f};
    const auto right {width * 0.5f};
    const auto top {height * 0.5f};
    const auto bottom {-height * 0.5f};

    return glm::ortho(left, right, bottom, top, near, far);
}

int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << '\n';
        return -1;
    }

    auto window {Renderer::Window {WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE}};
    if (!window.initialize()) {
        std::cerr << "ERROR: Failed to initialize window" << '\n';
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "ERROR: Failed to initialize GLAD" << '\n';
        window.destroy();
        glfwTerminate();
        return -1;
    }

    window.setCallbacks();

    auto projection {createOrthographicProjection(static_cast<float>(window.getWidth()) * Renderer::Utility::UNIT_SCALE,
                                                  static_cast<float>(window.getHeight()) *
                                                  Renderer::Utility::UNIT_SCALE, -1.0f, 1.0f)};

    auto binaryTreeMazeGenerator {std::make_unique<Core::BinaryTreeMazeGenerator>()};
    auto sidewinderMazeGenerator {std::make_unique<Core::SidewinderMazeGenerator>()};
    const auto mazeGenerators {std::array<std::unique_ptr<Core::MazeGenerator>, 2> {
            std::move(binaryTreeMazeGenerator),
            std::move(sidewinderMazeGenerator)
    }};

    auto squareGrid {Core::SquareGrid {SQUARE_GRID_SIZE}};
    squareGrid.initialize();

    auto mazeRenderer {Renderer::MazeRenderer {&squareGrid, Renderer::Utility::cellSize}};
    mazeRenderer.updateVertices();

    auto userInterface {Renderer::UserInterface {mazeGenerators, &mazeRenderer, &squareGrid, window}};
    userInterface.initialize();
    window.initializeImGui();

    auto timeSource {[]() noexcept {
        return static_cast<float>(glfwGetTime());
    }};

    auto deltaTimeCalculator {Renderer::Utility::DeltaTimeCalculator {timeSource}};

    while (!window.getShouldClose()) {
        const auto currentFrame {deltaTimeCalculator.update()};
        window.update(deltaTimeCalculator.getDeltaTime());
        userInterface.update(currentFrame);

        const auto aspectRatio {static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight())};
        mazeRenderer.update(deltaTimeCalculator.getDeltaTime(),
                            Renderer::Utility::cellSize,
                            Renderer::Utility::gridLineThickness,
                            aspectRatio,
                            userInterface.getGridColor());

        const auto backgroundColor {userInterface.getBackgroundColor()};
        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mazeRenderer.render(projection);
        userInterface.render();
        window.render();
    }

    mazeRenderer.destroy();
    window.destroy();
    glfwTerminate();

    return 0;
}