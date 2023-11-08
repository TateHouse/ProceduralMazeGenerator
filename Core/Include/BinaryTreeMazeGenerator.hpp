#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
class BinaryTreeMazeGenerator : public MazeGenerator {
public:
    BinaryTreeMazeGenerator() noexcept;
    BinaryTreeMazeGenerator(const BinaryTreeMazeGenerator& other) noexcept = default;
    BinaryTreeMazeGenerator(BinaryTreeMazeGenerator&& other) noexcept = default;
    virtual ~BinaryTreeMazeGenerator() noexcept override = default;

public:
    BinaryTreeMazeGenerator& operator=(const BinaryTreeMazeGenerator& other) noexcept = default;
    BinaryTreeMazeGenerator& operator=(BinaryTreeMazeGenerator&& other) noexcept = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}