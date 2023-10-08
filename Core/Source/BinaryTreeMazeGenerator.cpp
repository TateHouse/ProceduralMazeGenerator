#include "BinaryTreeMazeGenerator.hpp"

namespace Core {
BinaryTreeMazeGenerator::BinaryTreeMazeGenerator() noexcept: MazeGenerator {"Binary Tree Maze Algorithm"} {

}

void BinaryTreeMazeGenerator::generate(Core::Grid* const grid, const long long* seed) noexcept {
	auto randomEngine {getRandomEngine(seed)};
	std::uniform_int_distribution<std::size_t> distribution {};
	
	const auto [width, height] {grid->getSize()};
	
	for (std::size_t x {0}; x < width; ++x) {
		for (std::size_t y {0}; y < height; ++y) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			auto* const cell {(*grid)[{xPosition, yPosition}]};
			
			std::vector<Cell*> neighbors {};
			
			if (cell->getNorth() != nullptr) {
				neighbors.push_back(cell->getNorth());
			}
			
			if (cell->getEast() != nullptr) {
				neighbors.push_back(cell->getEast());
			}
			
			if (neighbors.empty()) {
				continue;
			}
			
			distribution.param(std::uniform_int_distribution<std::size_t>::param_type {0, neighbors.size() - 1});
			const auto index {distribution(randomEngine) % neighbors.size()};
			auto* neighbor {neighbors[index]};
			cell->link(neighbor);
		}
	}
}
}
