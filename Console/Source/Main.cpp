#include <iostream>
#include <memory>

#include "BinaryTreeMazeGenerator.hpp"
#include "ConsoleGridVisualizer.hpp"
#include "ConsoleMazeVisualizer.hpp"
#include "ImageVisualizer.hpp"
#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"

static constexpr auto GRID_SIZE {20};
static constexpr auto CELL_SIZE {20};
static constexpr auto BORDER_SIZE {5};
static const cv::Scalar BACKGROUND_COLOR {255.0f, 255.0f, 255.0f};
static const cv::Scalar GRID_COLOR {0.0f, 0.0f, 0.0f};

std::unique_ptr<Core::Grid> generateGrid() {
    auto grid {std::make_unique<Core::SquareGrid>(GRID_SIZE)};
    grid->initialize();
    return grid;
}

std::unique_ptr<Core::Grid> generateBinaryTreeMaze(const unsigned long long* seed) {
    auto grid {std::make_unique<Core::SquareGrid>(GRID_SIZE)};
    grid->initialize();
    Core::BinaryTreeMazeGenerator binaryTreeMazeGenerator {};
    binaryTreeMazeGenerator.generate(grid.get(), seed);

    return grid;
}

std::unique_ptr<Core::Grid> generateSidewinderMaze(const unsigned long long* seed) {
    auto grid {std::make_unique<Core::SquareGrid>(GRID_SIZE)};
    grid->initialize();
    Core::SidewinderMazeGenerator sidewinderMazeGenerator {};
    sidewinderMazeGenerator.generate(grid.get(), seed);

    return grid;
}

void exportImage(const Core::Grid* const grid, const std::filesystem::path& imagePath) noexcept {
    try {
        auto gridImageVisualizerBuilder {Core::ImageVisualizer::create(grid, imagePath)};
        gridImageVisualizerBuilder.setCellSize(CELL_SIZE);
        gridImageVisualizerBuilder.setBorderSize(BORDER_SIZE);
        gridImageVisualizerBuilder.setBackgroundColor(BACKGROUND_COLOR);
        gridImageVisualizerBuilder.setGridColor(GRID_COLOR);

        const auto gridImageVisualizer {gridImageVisualizerBuilder.build()};
        gridImageVisualizer->visualize();
        std::cout << "Export image to " << imagePath << '\n';
    } catch (const std::invalid_argument& exception) {
        std::cerr << exception.what() << '\n';
    }
}

void printGrid(const Core::Grid* const grid) noexcept {
    Console::ConsoleGridVisualizer consoleGridVisualizer {grid};
    consoleGridVisualizer.visualize();
}

void printMaze(const Core::Grid* const grid) noexcept {
    Console::ConsoleMazeVisualizer consoleMazeVisualizer {grid};
    consoleMazeVisualizer.visualize();
}

int main(int argc, char* argv[]) {
    auto grid {generateGrid()};
    auto binaryTreeMaze {generateBinaryTreeMaze(nullptr)};
    auto sidewinderMaze {generateSidewinderMaze(nullptr)};

    exportImage(grid.get(), "Images/Grid.png");
    exportImage(binaryTreeMaze.get(), "Images/BinaryTreeMaze.png");
    exportImage(sidewinderMaze.get(), "Images/SidewinderMaze.png");

    printGrid(grid.get());
    printMaze(binaryTreeMaze.get());
    printMaze(sidewinderMaze.get());

    return 0;
}