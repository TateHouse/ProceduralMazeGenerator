#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
/**
 * @brief Visualizes a maze in the console.
 * @class ConsoleMazeVisualizer
 */
class ConsoleMazeVisualizer : public Core::GridVisualizer {
public:
	/**
	 * @brief Instantiates a new console maze visualizer.
	 * @param grid The maze to visualize.
	 */
	explicit ConsoleMazeVisualizer(const Core::Grid* const grid) noexcept;
	
	/**
	 * @brief Instantiates a new console maze visualizer by copying the given console maze visualizer.
	 * @param other The console maze visualizer to copy.
	 */
	ConsoleMazeVisualizer(const ConsoleMazeVisualizer& other) = delete;
	
	/**
	 * @brief Instantiates a new console maze visualizer by moving the given console maze visualizer.
	 * @param other The console maze visualizer to move.
	 */
	ConsoleMazeVisualizer(ConsoleMazeVisualizer&& other) = delete;
	
	/**
	 * @brief Destroys the console maze visualizer.
	 */
	~ConsoleMazeVisualizer() noexcept override = default;

public:
	/**
	 * @brief Assigns the given console maze visualizer to this console maze visualizer using copy semantics.
	 * @param other The console maze visualizer to copy.
	 * @return A reference to this console maze visualizer.
	 */
	ConsoleMazeVisualizer& operator=(const ConsoleMazeVisualizer& other) = delete;
	
	/**
	 * @brief Assigns the given console maze visualizer to this console maze visualizer using move semantics.
	 * @param other The console maze visualizer to move.
	 * @return A reference to this console maze visualizer.
	 */
	ConsoleMazeVisualizer& operator=(ConsoleMazeVisualizer&& other) = delete;

public:
	void visualize() const noexcept override;

private:
	const Core::Grid* const grid;
};
}