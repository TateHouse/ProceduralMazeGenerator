#include <gmock/gmock.h>

#include <memory>

#include "BinaryTreeMazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Core::Test {
class BinaryTreeMazeGeneratorTest : public testing::Test {
public:
	BinaryTreeMazeGeneratorTest() noexcept {
		grid->initialize();
		mazeGenerator->generate(grid.get(), nullptr);
	}
	
	virtual ~BinaryTreeMazeGeneratorTest() noexcept = default;

protected:
    std::unique_ptr<Grid> grid {std::make_unique<SquareGrid>(5)};
	std::unique_ptr<MazeGenerator> mazeGenerator {std::make_unique<BinaryTreeMazeGenerator>()};
	const int width {grid->getSize().first};
	const int height {grid->getSize().second};
};

TEST_F(BinaryTreeMazeGeneratorTest,
       GivenBinaryTreeMazeGenerator_WhenGenerate_ThenNorthmostCellsAreLinkedToCreateHorizontalPassage) {
	static constexpr auto yPosition {4};
	
	for (std::size_t x {0}; x < width; ++x) {
		const auto xPosition {static_cast<int>(x)};
		const auto* const cell {(*grid)[{xPosition, yPosition}]};
		ASSERT_THAT(cell->getNorth(), testing::IsNull());
		
		if (x == 0) {
			EXPECT_THAT(cell->getLinks(), testing::Contains(cell->getEast()));
			EXPECT_THAT(cell->getWest(), testing::IsNull());
		} else if (x == width - 1) {
			EXPECT_THAT(cell->getLinks(), testing::Contains(cell->getWest()));
			EXPECT_THAT(cell->getEast(), testing::IsNull());
		} else {
			EXPECT_THAT(cell->getLinks(), testing::Contains(cell->getEast()));
			EXPECT_THAT(cell->getEast(), testing::NotNull());
		}
	}
}

TEST_F(BinaryTreeMazeGeneratorTest,
       GivenBinaryTreeMazeGenerator_WhenGenerate_ThenEastmostCellsAreLinkedToCreateVerticalPassage) {
	static constexpr auto xPosition {4};
	auto northLinkedCellCount {0};
	
	for (std::size_t y {0}; y < height; ++y) {
		const auto yPosition {static_cast<int>(y)};
		const auto* const cell {(*grid)[{xPosition, yPosition}]};
		ASSERT_THAT(cell->getEast(), testing::IsNull());
		
		if (cell->isLinked(cell->getNorth())) {
			++northLinkedCellCount;
		}
	}
	
	EXPECT_THAT(northLinkedCellCount, testing::Eq(height - 1));
}

TEST_F(BinaryTreeMazeGeneratorTest, GivenBinaryTreeMazeGenerator_WhenGenerate_ThenEveryCellHasBetweenOneAndThreeLinks) {
	for (std::size_t x {0}; x < width; ++x) {
		for (std::size_t y {0}; y < height; ++y) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			const auto* const cell {(*grid)[{xPosition, yPosition}]};
			const auto& links {cell->getLinks()};
			
			EXPECT_THAT(links, testing::SizeIs(testing::AnyOf(1, 2, 3)));
		}
	}
}

TEST_F(BinaryTreeMazeGeneratorTest,
       GivenBinaryTreeMazeGenerator_WhenGetMazeGenerationAlgorithmName_ThenReturnBinaryTree) {
	EXPECT_THAT(mazeGenerator->getAlgorithmName(), testing::StrCaseEq("Binary Tree"));
}
}