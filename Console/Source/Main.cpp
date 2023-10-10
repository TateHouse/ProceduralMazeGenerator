#include <memory>

#include "ConsoleGridVisualizer.hpp"
#include "SquareGrid.hpp"

int main(int argc, char* argv[]) {
	static constexpr std::size_t GRID_SIZE {10};
	std::unique_ptr<Core::Grid> grid {std::make_unique<Core::SquareGrid<GRID_SIZE>>()};
	grid->initialize();
	
	std::unique_ptr<Core::GridVisualizer> gridPrinter {std::make_unique<Console::ConsoleGridVisualizer>(grid.get())};
	gridPrinter->display();
	
	return 0;
}