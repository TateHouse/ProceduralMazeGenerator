#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class SidewinderMazeGenerator : public MazeGenerator {
public:
	SidewinderMazeGenerator() noexcept;
	virtual ~SidewinderMazeGenerator() noexcept override = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}