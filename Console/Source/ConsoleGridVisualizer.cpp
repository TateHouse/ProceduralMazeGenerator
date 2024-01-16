#include "ConsoleGridVisualizer.hpp"

#include <iostream>
#include <sstream>

namespace Console {
ConsoleGridVisualizer::ConsoleGridVisualizer(Core::Grid* grid) noexcept: grid {grid} {

}

void ConsoleGridVisualizer::visualize() const noexcept {
	std::stringstream stringStream {};
	
	stringStream << '+';
	
	auto [width, height] = grid->getSize();
	for (std::size_t x {0}; x < width; ++x) {
		stringStream << "---+";
	}
	
	for (std::size_t x {0}; x < width; ++x) {
		stringStream << '\n' << '|';
		
		for (std::size_t y {0}; y < height; ++y) {
			stringStream << "   |";
		}
		
		stringStream << '\n' << '+';
		
		for (std::size_t y {0}; y < height; ++y) {
			stringStream << "---+";
		}
	}

    stringStream << '\n';
	
	std::cout << stringStream.str();
}
}