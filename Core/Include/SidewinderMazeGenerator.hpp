#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
/**
 * @brief Modifies a grid to generate a maze using the sidewinder algorithm.
 * @class SidewinderMazeGenerator
 */
class SidewinderMazeGenerator : public MazeGenerator {
public:
	/**
	 * @brief Instantiates a new sidewinder maze generator.
	 */
	SidewinderMazeGenerator() noexcept;
	
	/**
	 * @brief Instantiates a new sidewinder maze generator by copying the given sidewinder maze generator.
	 * @param other The sidewinder maze generator to copy.
	 */
    SidewinderMazeGenerator(const SidewinderMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new sidewinder maze generator by moving the given sidewinder maze generator.
	 * @param other The sidewinder maze generator to move.
	 */
    SidewinderMazeGenerator(SidewinderMazeGenerator&& other) noexcept = default;
	
	/**
	 * @brief Destroys the sidewinder maze generator.
	 */
	~SidewinderMazeGenerator() noexcept override = default;

public:
	/**
	 * @brief Assigns the given sidewinder maze generator to this sidewinder maze generator using copy semantics.
	 * @param other The sidewinder maze generator to copy.
	 * @return A reference to this sidewinder maze generator.
	 */
    SidewinderMazeGenerator& operator=(const SidewinderMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Assigns the given sidewinder maze generator to this sidewinder maze generator using move semantics.
	 * @param other The sidewinder maze generator to move.
	 * @return A reference to this sidewinder maze generator.
	 */
    SidewinderMazeGenerator& operator=(SidewinderMazeGenerator&& other) noexcept = default;

public:
    void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}