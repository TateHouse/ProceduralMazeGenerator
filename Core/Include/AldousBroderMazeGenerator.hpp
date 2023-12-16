#pragma once

#include <optional>

#include "Grid.hpp"
#include "MazeGenerator.hpp"

namespace Core {
/**
 * @brief Modifies a grid to generate a maze using the Aldous-Broder algorithm.
 * @class AldousBroderMazeGenerator
 */
class AldousBroderMazeGenerator : public MazeGenerator {
public:
	/**
	 * @brief Instantiates a new aldous-broder maze generator.
	 */
	AldousBroderMazeGenerator() noexcept;
	
	/**
	 * @brief Instantiates a new aldous-broder maze generator by copying the given aldous-broder maze generator.
	 * @param other The aldous-broder maze generator to copy.
	 */
	AldousBroderMazeGenerator(const AldousBroderMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new aldous-broder maze generator by moving the given aldous-broder maze generator.
	 * @param other The aldous-broder maze generator to move.
	 */
	AldousBroderMazeGenerator(AldousBroderMazeGenerator&& other) noexcept = default;
	
	/**
	 * @brief Destroys the aldous-broder maze generator.
	 */
	~AldousBroderMazeGenerator() noexcept override = default;

public:
	/**
	 * @brief Assigns the given aldous-broder maze generator to this aldous-broder maze generator using copy semantics.
	 * @param other The aldous-broder maze generator to copy.
	 * @return A reference to this aldous-broder maze generator.
	 */
	AldousBroderMazeGenerator& operator=(const AldousBroderMazeGenerator& other) noexcept = default;
	
	/**
	 * @brief Assigns the given aldous-broder maze generator to this aldous-broder maze generator using move semantics.
	 * @param other The aldous-broder maze generator to move.
	 * @return A reference to this aldous-broder maze generator.
	 */
	AldousBroderMazeGenerator& operator=(AldousBroderMazeGenerator&& other) noexcept = default;

public:
	void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept override;
};
}