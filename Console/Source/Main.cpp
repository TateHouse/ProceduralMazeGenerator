#include <memory>

#include "ConsoleGridVisualizer.hpp"
#include "ImageGridVisualizer.hpp"
#include "SquareGrid.hpp"

int main(int argc, char* argv[]) {
	static constexpr std::size_t GRID_SIZE {10};
	std::unique_ptr<Core::Grid> grid {std::make_unique<Core::SquareGrid<GRID_SIZE>>()};
	grid->initialize();
	
	std::unique_ptr<Core::GridVisualizer> consoleGrid {std::make_unique<Console::ConsoleGridVisualizer>(grid.get())};
	consoleGrid->display();
	
	static constexpr unsigned int CELL_SIZE {50};
	static constexpr unsigned int BORDER_SIZE {10};
	static constexpr std::string_view IMAGE_PATH {"Images/Grid.png"};
	const cv::Scalar backgroundColor {255, 255, 255};
	const cv::Scalar gridColor {0, 0, 0};
	
	std::unique_ptr<Core::GridVisualizer> imageGrid {std::make_unique<Console::ImageGridVisualizer>(grid.get(),
	                                                                                                CELL_SIZE,
	                                                                                                BORDER_SIZE,
	                                                                                                IMAGE_PATH,
	                                                                                                backgroundColor,
	                                                                                                gridColor)};
	imageGrid->display();
	
	return 0;
}