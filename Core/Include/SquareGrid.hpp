#pragma once

#include <vector>

#include "Grid.hpp"

namespace Core {
class SquareGrid : public Grid {
public:
    explicit SquareGrid(const std::size_t size);
    SquareGrid(const SquareGrid& other) = delete;
    SquareGrid(SquareGrid&& other) noexcept = delete;
    ~SquareGrid() noexcept override;

public:
    SquareGrid& operator=(const SquareGrid& other) = delete;
    SquareGrid& operator=(SquareGrid&& other) noexcept = delete;

public:
    Cell* operator[](const std::pair<const int, const int>& position) noexcept override;
    const Cell* const operator[](const std::pair<const int, const int>& position) const noexcept override;

public:
    void initialize() override;
    void reset() noexcept override;
    [[nodiscard]] const std::pair<const int, const int> getSize() const noexcept override;

private:
    [[nodiscard]] const bool validateCellPosition(const std::pair<const int, const int>& position) const noexcept;
    void instantiateCells();
    void setCellNeighbors() noexcept;
    void deleteCells() noexcept;

private:
    std::vector<std::vector<Cell*>> cells {};
};
}