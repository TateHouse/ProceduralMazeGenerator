#include <gmock/gmock.h>

#include <memory>

#include "SquareGrid.hpp"

namespace Core::Test {
class SquareGridTest : public testing::Test {
public:
	SquareGridTest() noexcept: xSize {grid->getSize().first}, ySize {grid->getSize().second} {
		grid->initialize();
	}
	
	~SquareGridTest() noexcept override = default;

protected:
	std::unique_ptr<Grid> grid {std::make_unique<SquareGrid<5>>()};
	const int xSize;
	const int ySize;
};

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridHasSize) {
	EXPECT_THAT(grid->getSize(), testing::Eq(std::pair<int, int> {5, 5}));
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridContainsCorrectNumberOfCells) {
	auto cellCount {0};
	
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			if ((*grid)[position] != nullptr) {
				++cellCount;
			}
		}
	}
	
	const auto expectedCellCount {xSize * ySize};
	EXPECT_THAT(cellCount, testing::Eq(expectedCellCount));
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridCellsHaveCorrectNorthNeighbors) {
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			const auto* const cell {(*grid)[position]};
			const auto* const northNeighbor {cell->getNorth()};
			
			if (y < ySize - 1) {
				EXPECT_THAT(northNeighbor, testing::Eq(northNeighbor));
			} else {
				EXPECT_THAT(northNeighbor, testing::IsNull());
			}
		}
	}
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridCellsHaveCorrectWestNeighbors) {
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			const auto* const cell {(*grid)[position]};
			const auto* const westNeighbor {cell->getWest()};
			
			if (x > 0) {
				EXPECT_THAT(westNeighbor, testing::Eq(westNeighbor));
			} else {
				EXPECT_THAT(westNeighbor, testing::IsNull());
			}
		}
	}
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridCellsHaveCorrectSouthNeighbors) {
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			const auto* const cell {(*grid)[position]};
			const auto* const southNeighbor {cell->getSouth()};
			
			if (y > 0) {
				EXPECT_THAT(southNeighbor, testing::Eq(southNeighbor));
			} else {
				EXPECT_THAT(southNeighbor, testing::IsNull());
			}
		}
	}
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridCellsHaveCorrectEastNeighbors) {
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			const auto* const cell {(*grid)[position]};
			const auto* const eastNeighbor {cell->getEast()};
			
			if (x < xSize - 1) {
				EXPECT_THAT(eastNeighbor, testing::Eq(eastNeighbor));
			} else {
				EXPECT_THAT(eastNeighbor, testing::IsNull());
			}
		}
	}
}

TEST_F(SquareGridTest, GivenSize_WhenInstantiate_ThenGridCellsHaveNoLinks) {
	for (std::size_t x {0}; x < xSize; ++x) {
		for (std::size_t y {0}; y < ySize; ++y) {
			const auto position {std::pair {x, y}};
			const auto* const cell {(*grid)[position]};
			
			EXPECT_THAT(cell->getLinks(), testing::IsEmpty());
		}
	}
}
}