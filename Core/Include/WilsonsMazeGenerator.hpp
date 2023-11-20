#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class WilsonsMazeGenerator final : public MazeGenerator {
public:
	WilsonsMazeGenerator() noexcept;
	WilsonsMazeGenerator(const WilsonsMazeGenerator& other) noexcept = default;
	WilsonsMazeGenerator(WilsonsMazeGenerator&& other) noexcept = default;
	~WilsonsMazeGenerator() noexcept override = default;

public:
	WilsonsMazeGenerator& operator=(const WilsonsMazeGenerator& other) noexcept = default;
	WilsonsMazeGenerator& operator=(WilsonsMazeGenerator&& other) noexcept = default;

public:
	void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}