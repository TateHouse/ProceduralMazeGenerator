#include <memory>

#include "BinaryTreeMazeGenerator.hpp"
#include "ConsoleGridVisualizer.hpp"
#include "ConsoleMazeVisualizer.hpp"
#include "ImageGridVisualizer.hpp"
#include "ImageBinaryTreeMazeVisualizer.hpp"
#include "SquareGrid.hpp"

int main(int argc, char* argv[]) {
	static constexpr std::size_t MAZE_SIZE {10};
	std::unique_ptr<Core::Grid> maze {std::make_unique<Core::SquareGrid<MAZE_SIZE>>()};
	maze->initialize();
	
	std::unique_ptr<Core::GridVisualizer> imageGrid {std::make_unique<Console::ImageGridVisualizer>(maze.get(), 50,
	                                                                                                1,
	                                                                                                "Images/Grid.png",
	                                                                                                cv::Scalar(255,
	                                                                                                           255,
	                                                                                                           255),
	                                                                                                cv::Scalar(110,
	                                                                                                           20,
	                                                                                                           0))};
	imageGrid->display();
	
	std::unique_ptr<Core::MazeGenerator> mazeGenerator {std::make_unique<Core::BinaryTreeMazeGenerator>()};
	mazeGenerator->generate(maze.get(), nullptr);
	
	std::unique_ptr<Core::GridVisualizer> consoleMaze {std::make_unique<Console::ConsoleMazeVisualizer>(maze.get())};
	consoleMaze->display();
	std::cout << '\n';
	
	std::unique_ptr<Core::GridVisualizer> imageMaze {std::make_unique<Console::ImageBinaryTreeMazeVisualizer>(maze.get(),
	                                                                                                          20,
	                                                                                                          1,
	                                                                                                          "Images/Maze.png",
	                                                                                                          cv::Scalar(
			                                                                                                          255,
			                                                                                                          255,
			                                                                                                          255),
	                                                                                                          cv::Scalar(
			                                                                                                          110,
			                                                                                                          20,
			                                                                                                          0))};
	imageMaze->display();
	
	return 0;
}