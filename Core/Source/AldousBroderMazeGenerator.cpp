#include "AldousBroderMazeGenerator.hpp"

namespace Core {
AldousBroderMazeGenerator::AldousBroderMazeGenerator() noexcept: MazeGenerator {"AldousBroder"} {

}

void AldousBroderMazeGenerator::generate(Core::Grid* const grid,
                                         const std::optional<unsigned long long>& seed) noexcept {
	auto randomEngine {getRandomEngine(seed)};
	std::uniform_int_distribution<std::size_t> distribution {};
	const auto [width, height] {grid->getSize()};
	const auto randomX {static_cast<int>(distribution(randomEngine) % width)};
	const auto randomY {static_cast<int>(distribution(randomEngine) % height)};
	auto* cell {(*grid)[{randomX, randomY}]};
	auto unvisitedCells {width * height - 1};
	
	while (unvisitedCells > 0) {
		std::vector<Cell*> neighbors {cell->getNeighbors()};
		
		if (neighbors.empty()) {
			continue;
		}
		
		distribution.param(std::uniform_int_distribution<std::size_t>::param_type {0, neighbors.size() - 1});
		const auto index {distribution(randomEngine)};
		auto* neighbor {neighbors[index]};
		
		if (neighbor->getLinks().empty()) {
			cell->link(neighbor);
			--unvisitedCells;
		}
		
		cell = neighbor;
	}
}
}