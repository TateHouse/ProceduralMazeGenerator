#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
/**
 * @brief Visualizes a grid in the console.
 * @class ConsoleGridVisualizer
 */
class ConsoleGridVisualizer : public Core::GridVisualizer {
public:
	/**
	 * @brief Instantiates a new console grid visualizer.
	 * @param grid The grid to visualize.
	 */
	explicit ConsoleGridVisualizer(const Core::Grid* const grid) noexcept;
	
	/**
	 * @brief Instantiates a new console grid visualizer by copying the given console grid visualizer.
	 * @param other The console grid visualizer to copy.
	 */
    ConsoleGridVisualizer(const ConsoleGridVisualizer& other) = delete;
	
	/**
	 * @brief Instantiates a new console grid visualizer by moving the given console grid visualizer.
	 * @param other The console grid visualizer to move.
	 */
    ConsoleGridVisualizer(ConsoleGridVisualizer&& other) = delete;
	
	/**
	 * @brief Destroys the console grid visualizer.
	 */
	~ConsoleGridVisualizer() noexcept override = default;

public:
	/**
	 * @brief Assigns the given console grid visualizer to this console grid visualizer using copy semantics.
	 * @param other The console grid visualizer to copy.
	 * @return A reference to this console grid visualizer.
	 */
    ConsoleGridVisualizer& operator=(const ConsoleGridVisualizer& other) = delete;
	
	/**
	 * @brief Assigns the given console grid visualizer to this console grid visualizer using move semantics.
	 * @param other The console grid visualizer to move.
	 * @return
	 */
    ConsoleGridVisualizer& operator=(ConsoleGridVisualizer&& other) = delete;

public:
	void visualize() const noexcept override;

private:
	const Core::Grid* const grid;
};
}