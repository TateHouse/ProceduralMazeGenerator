#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class BinaryTreeMazeGenerator : public MazeGenerator {
public:
	BinaryTreeMazeGenerator() noexcept;
	virtual ~BinaryTreeMazeGenerator() noexcept override = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}