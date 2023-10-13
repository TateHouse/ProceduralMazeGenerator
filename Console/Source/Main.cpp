#include <memory>

#include "BinaryTreeMazeGenerator.hpp"
#include "ConsoleGridVisualizer.hpp"
#include "ConsoleMazeVisualizer.hpp"
#include "ImageGridVisualizer.hpp"
#include "SquareGrid.hpp"

int main(int argc, char* argv[]) {
	static constexpr std::size_t MAZE_SIZE {10};
	std::unique_ptr<Core::Grid> maze {std::make_unique<Core::SquareGrid<MAZE_SIZE>>()};
	maze->initialize();
	
	std::unique_ptr<Core::MazeGenerator> mazeGenerator {std::make_unique<Core::BinaryTreeMazeGenerator>()};
	mazeGenerator->generate(maze.get(), nullptr);
	
	std::unique_ptr<Core::GridVisualizer> consoleMaze {std::make_unique<Console::ConsoleMazeVisualizer>(maze.get())};
	consoleMaze->display();
	std::cout << '\n';
	
	return 0;
}