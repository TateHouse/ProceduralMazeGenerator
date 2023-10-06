#include "Cell.hpp"

#include <algorithm>

namespace Core {
Cell::Cell(int xPosition, int yPosition) noexcept: xPosition {xPosition}, yPosition {yPosition} {

}

void Cell::link(Cell* cell, const bool isBidirectional) noexcept {
	if (isBidirectional) {
		cell->link(this, false);
	}
	
	links.push_back(cell);
}

void Cell::unlink(Core::Cell* cell, const bool isBidirectional) noexcept {
	if (isBidirectional) {
		cell->unlink(this, false);
	}
	
	links.erase(std::ranges::remove(links, cell).begin(), links.end());
}

const int Cell::getXPosition() const noexcept {
	return xPosition;
}

const int Cell::getYPosition() const noexcept {
	return yPosition;
}

Cell* Cell::getNorth() const noexcept {
	return north;
}

Cell* Cell::getWest() const noexcept {
	return west;
}

Cell* Cell::getSouth() const noexcept {
	return south;
}

Cell* Cell::getEast() const noexcept {
	return east;
}

void Cell::setNorth(Cell* cell) noexcept {
	north = cell;
}

void Cell::setWest(Cell* cell) noexcept {
	west = cell;
}

void Cell::setSouth(Cell* cell) noexcept {
	south = cell;
}

void Cell::setEast(Cell* cell) noexcept {
	east = cell;
}

const std::vector<Cell*>& Cell::getLinks() noexcept {
	return links;
}
}