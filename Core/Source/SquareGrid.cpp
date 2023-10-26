#include "SquareGrid.hpp"

#include <stdexcept>

namespace Core {
SquareGrid::SquareGrid(const std::size_t size) {
    if (size < 1) {
        throw std::invalid_argument("Size must be greater than 0");
    }

    cells.resize(size);

    for (std::size_t x {0}; x < size; ++x) {
        cells[x].resize(size);
    }
}

SquareGrid::~SquareGrid() noexcept {
    const auto size {cells.size()};
    for (std::size_t x {0}; x < size; ++x) {
        for (std::size_t y {0}; y < size; ++y) {
            delete cells[x][y];
        }
    }
}

Cell* SquareGrid::operator[](const std::pair<const int, const int>& position) noexcept {
    const auto isValidPosition {validateCellPosition(position)};

    return isValidPosition ? cells[position.first][position.second] : nullptr;
}

const Cell* const SquareGrid::operator[](const std::pair<const int, const int>& position) const noexcept {
    const auto isValidPosition {validateCellPosition(position)};

    return isValidPosition ? cells[position.first][position.second] : nullptr;
}

void SquareGrid::initialize() {
    instantiateCells();
    setCellNeighbors();
}

const std::pair<const int, const int> SquareGrid::getSize() const noexcept {
    const auto size {cells.size()};
    const auto xSize {static_cast<int>(size)};
    const auto ySize {static_cast<int>(size)};

    return {xSize, ySize};
}

const bool SquareGrid::validateCellPosition(const std::pair<const int, const int>& position) const noexcept {
    const auto [xPosition, yPosition] {position};
    const auto size {cells.size()};

    if (xPosition < 0 || xPosition >= size || yPosition < 0 || yPosition >= size) {
        return false;
    }

    return true;
}

void SquareGrid::instantiateCells() {
    const auto size {cells.size()};

    for (std::size_t x {0}; x < size; ++x) {
        for (std::size_t y {0}; y < size; ++y) {
            const auto xPosition {static_cast<int>(x)};
            const auto yPosition {static_cast<int>(y)};
            cells[x][y] = new Cell {xPosition, yPosition};
        }
    }
}

void SquareGrid::setCellNeighbors() noexcept {
    const auto size {cells.size()};

    for (std::size_t x {0}; x < size; ++x) {
        for (std::size_t y {0}; y < size; ++y) {
            auto* const cell {cells[x][y]};

            if (y < size - 1) {
                cell->setNorth(cells[x][y + 1]);
            }

            if (x > 0) {
                cell->setWest(cells[x - 1][y]);
            }

            if (y > 0) {
                cell->setSouth(cells[x][y - 1]);
            }

            if (x < size - 1) {
                cell->setEast(cells[x + 1][y]);
            }
        }
    }
}
}
