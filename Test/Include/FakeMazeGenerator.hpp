#pragma once

#include "MazeGenerator.hpp"

namespace Core::Test {
class FakeMazeGenerator : public MazeGenerator {
public:
	FakeMazeGenerator() noexcept: MazeGenerator {"Mock Maze Generator"} {
	
	}
	
	void generate(Grid* const grid, const unsigned long long int* seed) noexcept override {
		getRandomEngine(seed);
	}
};
}