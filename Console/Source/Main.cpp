#include "BinaryTreeMazeGenerator.hpp"
#include "ImageBinaryTreeMazeVisualizer.hpp"
#include "ImageGridVisualizer.hpp"
#include "SquareGrid.hpp"

int main(int argc, char* argv[]) {
	static constexpr auto GRID_WIDTH {20};
	Core::Grid* grid {new Core::SquareGrid<GRID_WIDTH>};
	grid->initialize();
	
	static constexpr auto CELL_SIZE {20};
	static constexpr auto BORDER_SIZE {2};
	static const cv::Scalar BACKGROUND_COLOR {255, 255, 255};
	static const cv::Scalar GRID_COLOR {0, 0, 0};
	
	Core::GridVisualizer* imageVisualizer {new Console::ImageGridVisualizer(grid,
	                                                                        CELL_SIZE,
	                                                                        BORDER_SIZE,
	                                                                        "Grid.png",
	                                                                        BACKGROUND_COLOR,
	                                                                        GRID_COLOR)};
	imageVisualizer->visualize();
	
	Core::MazeGenerator* mazeGenerator {new Core::BinaryTreeMazeGenerator()};
	mazeGenerator->generate(grid, nullptr);
	
	delete imageVisualizer;
	imageVisualizer = new Console::ImageBinaryTreeMazeVisualizer(grid,
	                                                             CELL_SIZE,
	                                                             BORDER_SIZE,
	                                                             "Maze.png",
	                                                             BACKGROUND_COLOR,
	                                                             GRID_COLOR);
	imageVisualizer->visualize();
	
	delete imageVisualizer;
	delete mazeGenerator;
	delete grid;
	
	return 0;
}