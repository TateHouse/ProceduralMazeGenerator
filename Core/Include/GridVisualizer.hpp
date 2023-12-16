#pragma once

namespace Core {
/**
 * @brief An interface for visualizing a grid.
 * @class GridVisualizer
 */
class GridVisualizer {
public:
	/**
	 * @brief Destroys the grid visualizer.
	 */
    virtual ~GridVisualizer() noexcept = default;

public:
	/**
	 * @brief Visualizes the grid.
	 */
    virtual void visualize() const noexcept = 0;
};
}