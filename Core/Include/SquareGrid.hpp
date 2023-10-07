#pragma once

#include <array>

#include "Grid.hpp"

namespace Core {
template<std::size_t Size>
class SquareGrid : public Grid {
public:
	~SquareGrid() noexcept override {
		for (std::size_t x {0}; x < Size; ++x) {
			for (std::size_t y {0}; y < Size; ++y) {
				delete cells[x][y];
			}
		}
	}

public:
	Cell* operator[](const std::pair<const int, const int>& position) const noexcept override {
		const auto [xPosition, yPosition] {position};
		
		if (xPosition < 0 || xPosition >= Size || yPosition < 0 || yPosition >= Size) {
			return nullptr;
		}
		
		return cells[xPosition][yPosition];
	}

public:
	void initialize() noexcept override {
		instantiateCells();
		setCellNeighbors();
	}
	
	[[nodiscard]] const std::pair<int, int> getSize() const noexcept override {
		constexpr auto xSize {static_cast<int>(Size)};
		constexpr auto ySize {static_cast<int>(Size)};
		
		return {xSize, ySize};
	}

private:
	void instantiateCells() noexcept {
		for (std::size_t x {0}; x < Size; ++x) {
			for (std::size_t y {0}; y < Size; ++y) {
				const auto xPosition {static_cast<int>(x)};
				const auto yPosition {static_cast<int>(y)};
				cells[x][y] = new Cell {xPosition, yPosition};
			}
		}
	}
	
	void setCellNeighbors() noexcept {
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

private:
	std::array<std::array<Cell*, Size>, Size> cells;
};
}