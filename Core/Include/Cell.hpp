#pragma once

#include <vector>

namespace Core {
/**
 * @brief A cell in a maze.
 * @class Cell
 */
class Cell {
public:
	/**
	 * @brief Instantiates a new cell.
	 * @param xPosition The x position of the cell.
	 * @param yPosition The y position of the cell.
	 */
	Cell(int xPosition, int yPosition) noexcept;
	
	/**
	 * @brief Instantiates a new cell by copying the given cell.
	 * @param cell The cell to copy.
	 */
	Cell(const Cell& cell) noexcept = default;
	
	/**
	 * @brief Instantiates a new cell by moving the given cell.
	 * @param cell The cell to move.
	 */
	Cell(Cell&& cell) noexcept = default;
	
	/**
	 * @brief Destroys the cell.
	 */
	~Cell() noexcept = default;

public:
	/**
	 * @brief Assigns the given cell to this cell using copy semantics.
	 * @param cell The cell to copy.
	 * @return A reference to this cell.
	 */
	Cell& operator=(const Cell& cell) noexcept = default;
	
	/**
	 * @brief Assigns the given cell to this cell using move semantics.
	 * @param cell The cell to move.
	 * @return A reference to this cell.
	 */
	Cell& operator=(Cell&& cell) noexcept = default;

public:
	/**
	 * @brief Links this cell to the given cell.
	 * @param cell The cell to link to.
	 * @param isBidirectional Whether or not the link is bidirectional.
	 */
	void link(Cell* cell, const bool isBidirectional = true) noexcept;
	
	/**
	 * @brief Unlinks this cell from the given cell.
	 * @param cell The cell to unlink from.
	 * @param isBidirectional Whether or not the link is bidirectional.
	 */
	void unlink(Cell* cell, const bool isBidirectional = true) noexcept;
	
	/**
	 * @brief Checks if this cell is linked to the given cell.
	 * @param cell The cell to check.
	 * @return True if this cell is linked to the given cell, false otherwise.
	 */
	[[nodiscard]] bool isLinked(const Cell* const cell) const noexcept;
	
	/**
	 * @brief Gets the links of this cell.
	 * @return The links of this cell.
	 */
	[[nodiscard]] const std::vector<Cell*>& getLinks() const noexcept;
	
	/**
	 * @brief Gets the x position of this cell.
	 * @return The x position of this cell.
	 */
	[[nodiscard]] int getXPosition() const noexcept;
	
	/**
	 * @brief Gets the y position of this cell.
	 * @return The y position of this cell.
	 */
	[[nodiscard]] int getYPosition() const noexcept;
	
	/**
	 * @brief Gets the neighbors of this cell.
	 * @details The order of the neighbors is north, west, south, east. If a neighbor does not exist, then it will not
	 * be included in the returned vector.
	 * @return The neighbors of this cell.
	 */
	[[nodiscard]] std::vector<Cell*> getNeighbors() const noexcept;
	
	/**
	 * @brief Gets a pointer to the cell to the north of this cell.
	 * @return A pointer to the cell to the north of this cell.
	 */
	[[nodiscard]] Cell* getNorth() const noexcept;
	
	/**
	 * @brief Gets a pointer to the cell to the west of this cell.
	 * @return A pointer to the cell to the west of this cell.
	 */
	[[nodiscard]] Cell* getWest() const noexcept;
	
	/**
	 * @brief Gets a pointer to the cell to the south of this cell.
	 * @return A pointer to the cell to the south of this cell.
	 */
	[[nodiscard]] Cell* getSouth() const noexcept;
	
	/**
	 * @brief Gets a pointer to the cell to the east of this cell.
	 * @return A pointer to the cell to the east of this cell.
	 */
	[[nodiscard]] Cell* getEast() const noexcept;
	
	/**
	 * @brief Sets the cell to the north of this cell.
	 * @param cell A pointer to the cell to the north of this cell.
	 */
	void setNorth(Cell* cell) noexcept;
	
	/**
	 * @brief Sets the cell to the west of this cell.
	 * @param cell A pointer to the cell to the west of this cell.
	 */
	void setWest(Cell* cell) noexcept;
	
	/**
	 * @brief Sets the cell to the south of this cell.
	 * @param cell A pointer to the cell to the south of this cell.
	 */
	void setSouth(Cell* cell) noexcept;
	
	/**
	 * @brief Sets the cell to the east of this cell.
	 * @param cell A pointer to the cell to the east of this cell.
	 */
	void setEast(Cell* cell) noexcept;

private:
	int xPosition;
	int yPosition;
	Cell* north {nullptr};
	Cell* west {nullptr};
	Cell* south {nullptr};
	Cell* east {nullptr};
	std::vector<Cell*> links;
};
}