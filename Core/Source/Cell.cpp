#include "Cell.hpp"

#include <algorithm>
#include <array>
#include <iterator>

namespace Core {
Cell::Cell(int xPosition, int yPosition) noexcept: xPosition {xPosition}, yPosition {yPosition} {

}

void Cell::link(Cell* cell, const bool isBidirectional) noexcept {
	if (isLinked(cell)) {
		return;
	}
	
	if (isBidirectional) {
		cell->link(this, false);
	}
	
	links.push_back(cell);
}

void Cell::unlink(Core::Cell* cell, const bool isBidirectional) noexcept {
	if (!isLinked(cell)) {
		return;
	}
	
	if (isBidirectional) {
		cell->unlink(this, false);
	}
	
	links.erase(std::ranges::remove(links, cell).begin(), links.end());
}

bool Cell::isLinked(const Cell* const cell) const noexcept {
	return std::ranges::find(links, cell) != links.end();
}

const std::vector<Cell*>& Cell::getLinks() const noexcept {
	return links;
}

int Cell::getXPosition() const noexcept {
	return xPosition;
}

int Cell::getYPosition() const noexcept {
	return yPosition;
}

std::vector<Cell*> Cell::getNeighbors() const noexcept {
	std::array<Cell*, 4> directions {north, west, south, east};
	std::vector<Cell*> neighbors {};
	neighbors.reserve(directions.size());
	
	std::ranges::copy_if(directions, std::back_inserter(neighbors), [](const Cell* const cell) {
		return cell != nullptr;
	});
	
	return neighbors;
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
}