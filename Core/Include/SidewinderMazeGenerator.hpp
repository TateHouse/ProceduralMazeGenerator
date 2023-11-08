#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class SidewinderMazeGenerator : public MazeGenerator {
public:
	SidewinderMazeGenerator() noexcept;
    SidewinderMazeGenerator(const SidewinderMazeGenerator& other) noexcept = default;
    SidewinderMazeGenerator(SidewinderMazeGenerator&& other) noexcept = default;
	virtual ~SidewinderMazeGenerator() noexcept override = default;

public:
    SidewinderMazeGenerator& operator=(const SidewinderMazeGenerator& other) noexcept = default;
    SidewinderMazeGenerator& operator=(SidewinderMazeGenerator&& other) noexcept = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}