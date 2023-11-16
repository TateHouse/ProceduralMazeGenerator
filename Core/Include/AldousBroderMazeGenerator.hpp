#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class AldousBroderMazeGenerator : public MazeGenerator {
public:
	AldousBroderMazeGenerator() noexcept;
	AldousBroderMazeGenerator(const AldousBroderMazeGenerator& other) noexcept = default;
	AldousBroderMazeGenerator(AldousBroderMazeGenerator&& other) noexcept = default;
	virtual ~AldousBroderMazeGenerator() noexcept override = default;

public:
	AldousBroderMazeGenerator& operator=(const AldousBroderMazeGenerator& other) noexcept = default;
	AldousBroderMazeGenerator& operator=(AldousBroderMazeGenerator&& other) noexcept = default;

public:
	void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}