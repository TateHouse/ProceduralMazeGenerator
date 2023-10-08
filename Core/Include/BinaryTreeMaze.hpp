#pragma once

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
template<std::size_t Width, std::size_t Height>
class BinaryTreeMazeGenerator : public MazeGenerator {
public:
	BinaryTreeMazeGenerator() noexcept: MazeGenerator {"Binary Tree Maze Algorithm"} {
	
	}
	
	virtual ~BinaryTreeMazeGenerator() noexcept override = default;

public:
	void generate(Grid* const grid, const long long int* seed) noexcept override {
		auto randomEngine {getRandomEngine(seed)};
		std::uniform_int_distribution<std::size_t> distribution {};
		
		for (std::size_t x {0}; x < Width; ++x) {
			for (std::size_t y {0}; y < Height; ++y) {
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
};
}