#pragma once

#include <vector>

namespace Core {
class Cell {
public:
	Cell(int xPosition, int yPosition) noexcept;
	
	void link(Cell* cell, const bool isBidirectional = true) noexcept;
	void unlink(Cell* cell, const bool isBidirectional = true) noexcept;

public:
	[[nodiscard]] const int getXPosition() const noexcept;
	[[nodiscard]] const int getYPosition() const noexcept;
	
	[[nodiscard]] Cell* getNorth() const noexcept;
	[[nodiscard]] Cell* getWest() const noexcept;
	[[nodiscard]] Cell* getSouth() const noexcept;
	[[nodiscard]] Cell* getEast() const noexcept;
	
	void setNorth(Cell* cell) noexcept;
	void setWest(Cell* cell) noexcept;
	void setSouth(Cell* cell) noexcept;
	void setEast(Cell* cell) noexcept;
	
	[[nodiscard]] const std::vector<Cell*>& getLinks() noexcept;

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