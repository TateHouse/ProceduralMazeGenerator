#include "SidewinderMazeGenerator.hpp"

#include <vector>

namespace Core {
SidewinderMazeGenerator::SidewinderMazeGenerator() noexcept: MazeGenerator {"Sidewinder Maze Algorithm"} {

}

void SidewinderMazeGenerator::generate(Core::Grid* const grid, const unsigned long long* seed) noexcept {
	auto randomEngine {getRandomEngine(seed)};
	std::uniform_int_distribution<std::size_t> distribution {};
	distribution.param(std::uniform_int_distribution<std::size_t>::param_type {0, 1});
	
	const auto [width, height] {grid->getSize()};
	
	for (std::size_t y {0}; y < height; ++y) {
		std::vector<Cell*> run {};
		
		for (std::size_t x {0}; x < width; ++x) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			auto* cell {(*grid)[{xPosition, yPosition}]};
			
			run.push_back(cell);
			
			const auto* const northNeighbor {cell->getNorth()};
			const auto* const eastNeighbor {cell->getEast()};
			
			const bool isAtNorthernBoundary {northNeighbor == nullptr};
			const bool isAtEasternBoundary {eastNeighbor == nullptr};
			
			const bool shouldCloseOut {isAtEasternBoundary || !isAtNorthernBoundary && distribution(randomEngine) == 0};
			if (shouldCloseOut) {
				auto runDistribution {std::uniform_int_distribution<std::size_t> {0, run.size() - 1}};
				const auto index {runDistribution(randomEngine) % run.size()};
				
				if (auto* member {run[index]}; member->getNorth() != nullptr) {
					member->link(member->getNorth());
				}
				
				run.clear();
			} else {
				cell->link(cell->getEast());
			}
		}
	}
}
}