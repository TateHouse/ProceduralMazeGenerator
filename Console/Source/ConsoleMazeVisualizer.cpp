#include "ConsoleMazeVisualizer.hpp"

#include <iostream>
#include <sstream>

namespace Console {
ConsoleMazeVisualizer::ConsoleMazeVisualizer(const Core::Grid* const grid) noexcept: grid {grid} {

}

void ConsoleMazeVisualizer::visualize() const noexcept {
	std::stringstream stringStream {};
	
	stringStream << '+';
	
	auto [width, height] = grid->getSize();
	for (std::size_t x {0}; x < width; ++x) {
		stringStream << "---+";
	}
	
	stringStream << '\n';
	
	for (auto row {height - 1}; row >= 0; --row) {
		std::string top {'|'};
		std::string bottom {'+'};
		std::string body {"   "};
		
		for (std::size_t column {0}; column < width; ++column) {
			const auto position {std::pair<const int, const int> {static_cast<int>(column), row}};
			const auto* const cell {(*grid)[position]};
			const auto* const eastNeighbor {cell->getEast()};
			const auto* const southNeighbor {cell->getSouth()};
			
			std::string eastBoundary {eastNeighbor && cell->isLinked(eastNeighbor) ? " " : "|"};
			top += body + eastBoundary;
			
			std::string southBoundary {southNeighbor && cell->isLinked(southNeighbor) ? "   " : "---"};
			const std::string corner {"+"};
			bottom += southBoundary + corner;
		}
		
		stringStream << top << '\n';
		stringStream << bottom << '\n';
	}
	
	std::cout << stringStream.str();
}
}