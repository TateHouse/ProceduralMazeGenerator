#pragma once

#include <vector>

#include "Grid.hpp"

namespace Core {
class SquareGrid : public Grid {
public:
    SquareGrid(const std::size_t size);
    ~SquareGrid() noexcept override;

public:
    Cell* operator[](const std::pair<const int, const int>& position) noexcept override;
    const Cell* const operator[](const std::pair<const int, const int>& position) const noexcept override;

public:
    void initialize() override;
    void reset() noexcept override;
    [[nodiscard]] const std::pair<const int, const int> getSize() const noexcept override;

private:
    [[nosiscard]] const bool validateCellPosition(const std::pair<const int, const int>& position) const noexcept;
    void instantiateCells();
    void setCellNeighbors() noexcept;
    void deleteCells() noexcept;

private:
    std::vector<std::vector<Cell*>> cells {};
};
}