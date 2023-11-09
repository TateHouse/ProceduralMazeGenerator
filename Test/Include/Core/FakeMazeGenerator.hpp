#pragma once

#include <optional>

#include "MazeGenerator.hpp"

namespace Core::Test {
class FakeMazeGenerator : public MazeGenerator {
public:
	FakeMazeGenerator() noexcept: MazeGenerator {"Mock Maze Generator"} {
	
	}

    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override {
		getRandomEngine(seed);
	}
};
}