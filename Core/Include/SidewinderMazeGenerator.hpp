#pragma once

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class SidewinderMazeGenerator : public MazeGenerator {
public:
	SidewinderMazeGenerator() noexcept;
	virtual ~SidewinderMazeGenerator() noexcept override = default;

public:
	void generate(Grid* const grid, const unsigned long long int* seed) noexcept override;
};
}