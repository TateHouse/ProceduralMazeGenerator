#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
/**
 * @brief Modifies a grid to generate a maze using the binary tree algorithm.
 * @class BinaryTreeMazeGenerator
 */
class BinaryTreeMazeGenerator : public MazeGenerator {
public:
	/**
	 * @brief Instantiates a new binary tree maze generator.
	 */
    BinaryTreeMazeGenerator() noexcept;
	
	/**
	 * @brief Instantiates a new binary tree maze generator by copying the given binary tree maze generator.
	 * @param other The binary tree maze generator to copy.
	 */
    BinaryTreeMazeGenerator(const BinaryTreeMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new binary tree maze generator by moving the given binary tree maze generator.
	 * @param other The binary tree maze generator to move.
	 */
    BinaryTreeMazeGenerator(BinaryTreeMazeGenerator&& other) noexcept = default;
	
	/**
	 * @brief Destroys the binary tree maze generator.
	 */
	~BinaryTreeMazeGenerator() noexcept override = default;

public:
	/**
	 * @brief Assigns the given binary tree maze generator to this binary tree maze generator using copy semantics.
	 * @param other The binary tree maze generator to copy.
	 * @return A reference to this binary tree maze generator.
	 */
    BinaryTreeMazeGenerator& operator=(const BinaryTreeMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Assigns the given binary tree maze generator to this binary tree maze generator using move semantics.
	 * @param other The binary tree maze generator to move.
	 * @return A reference to this binary tree maze generator.
	 */
    BinaryTreeMazeGenerator& operator=(BinaryTreeMazeGenerator&& other) noexcept = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}