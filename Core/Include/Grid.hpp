#pragma once

#include "Cell.hpp"

namespace Core {
/**
 * @brief An interface for a grid of cells.
 * @class Grid
 */
class Grid {
public:
	/**
	 * @brief Destroys the grid.
	 */
    virtual ~Grid() noexcept = default;

public:
	/**
	 * @brief Gets a pointer to the cell at the given (x, y) position.
	 * @param position The (x, y) position of the cell.
	 * @return A pointer to the cell at the given (x, y) position.
	 */
	virtual Cell* operator[](const std::pair<const int, const int>& position) noexcept = 0;
	
	/**
	 * @brief Gets a const pointer to the const cell at the given (x, y) position.
	 * @param position The (x, y) position of the cell.
	 * @return A const pointer to the const cell at the given (x, y) position.
	 */
	virtual const Cell* const operator[](const std::pair<const int, const int>& position) const noexcept = 0;

public:
	/**
	 * @brief Initializes the grid.
	 * @details This method must be called before using the grid.
	 */
    virtual void initialize() = 0;
	
	/**
	 * @brief Gets the x and y sizes of the grid.
	 * @return The x and y sizes of the grid.
	 */
	[[nodiscard]] virtual const std::pair<const int, const int> getSize() const noexcept = 0;
	
	/**
	 * @brief Resets the grid.
	 */
    virtual void reset() noexcept = 0;
};
}