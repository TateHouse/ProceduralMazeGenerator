#include "WilsonsMazeGenerator.hpp"

#include <unordered_set>

namespace Core {
WilsonsMazeGenerator::WilsonsMazeGenerator() noexcept: MazeGenerator {"Wilsons"} {

}

void WilsonsMazeGenerator::generate(Core::Grid* const grid, const std::optional<unsigned long long>& seed) noexcept {
	std::vector<Cell*> unvisitedCells {};
	const auto [width, height] {grid->getSize()};
	
	for (std::size_t x {0}; x < width; ++x) {
		for (std::size_t y {0}; y < height; ++y) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			unvisitedCells.push_back((*grid)[{xPosition, yPosition}]);
		}
	}
	
	if (unvisitedCells.empty()) {
		return;
	}
	
	auto randomEngine {getRandomEngine(seed)};
	std::uniform_int_distribution<std::size_t> directionDistribution {0, 3};
	std::uniform_int_distribution<std::size_t> cellDistribution {};
	cellDistribution.param(std::uniform_int_distribution<std::size_t>::param_type {0, unvisitedCells.size() - 1});
	
	const auto randomIndex {cellDistribution(randomEngine)};
	unvisitedCells.erase(unvisitedCells.begin() + static_cast<unsigned int>(randomIndex));
	
	while (!unvisitedCells.empty()) {
		cellDistribution.param(std::uniform_int_distribution<std::size_t>::param_type {0, unvisitedCells.size() - 1});
		const auto randomIndex {cellDistribution(randomEngine)};
		auto* cell {unvisitedCells[randomIndex]};
		std::vector<Cell*> path {cell};
		std::unordered_set<Cell*> pathSet {cell};
		
		while (std::ranges::find(unvisitedCells, cell) != unvisitedCells.end()) {
			const auto xPosition {cell->getXPosition()};
			const auto yPosition {cell->getYPosition()};
			
			if (const auto randomDirection {directionDistribution(randomEngine)}; randomDirection == 0 &&
			                                                                      yPosition > 0) {
				cell = (*grid)[{xPosition, yPosition - 1}];
			} else if (randomDirection == 1 && xPosition > 0) {
				cell = (*grid)[{xPosition - 1, yPosition}];
			} else if (randomDirection == 2 && yPosition < height - 1) {
				cell = (*grid)[{xPosition, yPosition + 1}];
			} else if (randomDirection == 3 && xPosition < width - 1) {
				cell = (*grid)[{xPosition + 1, yPosition}];
			}
			
			if (pathSet.contains(cell)) {
				while (cell != path.back()) {
					pathSet.erase(path.back());
					path.pop_back();
				}
			} else {
				path.push_back(cell);
				pathSet.insert(cell);
			}
		}
		
		for (std::size_t index {0}; index < path.size() - 1; ++index) {
			path[index]->link(path[index + 1]);
			auto iterator {std::ranges::find(unvisitedCells, path[index])};
			if (iterator != unvisitedCells.end()) {
				unvisitedCells.erase(iterator);
			}
		}
	}
}
}