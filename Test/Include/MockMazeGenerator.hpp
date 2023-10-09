#pragma once

#include <gmock/gmock.h>

#include "MazeGenerator.hpp"

namespace Core::Test {
class MockMazeGenerator : public MazeGenerator {
public:
	MockMazeGenerator() noexcept: MazeGenerator {"Mock Maze Generator"} {
	
	}

public:
	MOCK_METHOD(void, generate, (Grid * const grid, const unsigned long long* seed), (noexcept, override));

public:
	void getRandomEngineWrapper(const unsigned long long* seed) noexcept {
		getRandomEngine(seed);
	}
};
}