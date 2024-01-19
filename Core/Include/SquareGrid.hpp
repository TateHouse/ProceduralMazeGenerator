#pragma once

#include <vector>

#include "Grid.hpp"

namespace Core {
/**
 * @brief A square grid of cells.
 * @class SquareGrid
 */
class SquareGrid : public Grid {
public:
	/**
	 * @brief Instantiates a new square grid.
	 * @param size The size of the grid. The size must be greater than 0.
	 * @throws std::invalid_argument Thrown if the size is not greater than 0.
	 */
    explicit SquareGrid(const std::size_t size);
	
	/**
	 * @brief Instantiates a new square grid by copying the given square grid.
	 * @param other The square grid to copy.
	 */
    SquareGrid(const SquareGrid& other) = delete;
	
	/**
	 * @brief Instantiates a new square grid by moving the given square grid.
	 * @param other The square grid to move.
	 */
    SquareGrid(SquareGrid&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the square grid.
	 */
    ~SquareGrid() noexcept override;

public:
	/**
	 * @brief Assigns the given square grid to this square grid using copy semantics.
	 * @param other The square grid to copy.
	 * @return A reference to this square grid.
	 */
    SquareGrid& operator=(const SquareGrid& other) = delete;
	
	/**
	 * @brief Assigns the given square grid to this square grid using move semantics.
	 * @param other The square grid to move.
	 * @return A reference to this square grid.
	 */
    SquareGrid& operator=(SquareGrid&& other) noexcept = delete;

public:
    Cell* operator[](const std::pair<const int, const int>& position) noexcept override;
    const Cell* const operator[](const std::pair<const int, const int>& position) const noexcept override;

public:
    void initialize() override;
    void reset() noexcept override;
    [[nodiscard]] const std::pair<const int, const int> getSize() const noexcept override;

private:
	/**
	 * @brief Validates the given cell position is within the bounds of the grid.
	 * @param position The cell position to validate.
	 * @return True if the given cell position is valid; false otherwise.
	 */
    [[nodiscard]] bool validateCellPosition(const std::pair<const int, const int>& position) const noexcept;
	
	/**
	 * @brief Instantiates the cells of the grid.
	 */
    void instantiateCells();
	
	/**
	 * @brief Sets the default neighbors of the cells of the grid.
	 */
    void setCellNeighbors() noexcept;
	
	/**
	 * @brief Deletes the cells of the grid.
	 */
    void deleteCells() noexcept;

private:
    std::vector<std::vector<Cell*>> cells {};
};
}