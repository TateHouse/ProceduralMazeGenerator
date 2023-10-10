#pragma once

#include <array>

#include "Grid.hpp"

namespace Core {
template<std::size_t Size>
class SquareGrid : public Grid {
public:
	~SquareGrid() noexcept override;

public:
	Cell* operator[](const std::pair<const int, const int>& position) const noexcept override;

public:
	void initialize() noexcept override;
	[[nodiscard]] const std::pair<const int, const int> getSize() const noexcept override;

private:
	void instantiateCells() noexcept;
	void setCellNeighbors() noexcept;

private:
	std::array<std::array<Cell*, Size>, Size> cells;
};

template<std::size_t Size>
SquareGrid<Size>::~SquareGrid() noexcept {
	for (std::size_t x {0}; x < Size; ++x) {
		for (std::size_t y {0}; y < Size; ++y) {
			delete cells[x][y];
		}
	}
}

template<std::size_t Size>
Cell* SquareGrid<Size>::operator[](const std::pair<const int, const int>& position) const noexcept {
	const auto [xPosition, yPosition] {position};
	
	if (xPosition < 0 || xPosition >= Size || yPosition < 0 || yPosition >= Size) {
		return nullptr;
	}
	
	return cells[xPosition][yPosition];
}

template<std::size_t Size>
void SquareGrid<Size>::initialize() noexcept {
	instantiateCells();
	setCellNeighbors();
}

template<std::size_t Size>
const std::pair<const int, const int> SquareGrid<Size>::getSize() const noexcept {
	constexpr auto xSize {static_cast<int>(Size)};
	constexpr auto ySize {static_cast<int>(Size)};
	
	return {xSize, ySize};
}

template<std::size_t Size>
void SquareGrid<Size>::instantiateCells() noexcept {
	for (std::size_t x {0}; x < Size; ++x) {
		for (std::size_t y {0}; y < Size; ++y) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			cells[x][y] = new Cell {xPosition, yPosition};
		}
	}
}

template<std::size_t Size>
void SquareGrid<Size>::setCellNeighbors() noexcept {
	for (std::size_t x {0}; x < Size; ++x) {
		for (std::size_t y {0}; y < Size; ++y) {
			auto* const cell {cells[x][y]};
			
			if (y < Size - 1) {
				cell->setNorth(cells[x][y + 1]);
			}
			
			if (x > 0) {
				cell->setWest(cells[x - 1][y]);
			}
			
			if (y > 0) {
				cell->setSouth(cells[x][y - 1]);
			}
			
			if (x < Size - 1) {
				cell->setEast(cells[x + 1][y]);
			}
		}
	}
}
}