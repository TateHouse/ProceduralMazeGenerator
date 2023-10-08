#include <gmock/gmock.h>

#include <array>
#include <memory>

#include "Cell.hpp"

namespace Core::Test {
class CellAttributeTest : public testing::Test {
public:
	CellAttributeTest() noexcept = default;
	~CellAttributeTest() noexcept override = default;

protected:
	void CustomSetUp(std::pair<int, int> firstPosition, std::pair<int, int> secondPosition) noexcept {
		firstCell = std::make_unique<Cell>(firstPosition.first, firstPosition.second);
		secondCell = std::make_unique<Cell>(secondPosition.first, secondPosition.second);
	}
	
	std::unique_ptr<Cell> firstCell {nullptr};
	std::unique_ptr<Cell> secondCell {nullptr};
};

TEST_F(CellAttributeTest, GivenTwoCells_WhenGetXPosition_ThenReturnsXPosition) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getXPosition(), testing::Eq(0));
	EXPECT_THAT(secondCell->getXPosition(), testing::Eq(0));
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenGetYPosition_ThenReturnsYPosition) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getYPosition(), testing::Eq(0));
	EXPECT_THAT(secondCell->getYPosition(), testing::Eq(1));
}

TEST_F(CellAttributeTest, GivenTwoCellsWithoutNeighbors_WhenGetNeighbors_ThenReturnsEmptyVector) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getNeighbors(), testing::IsEmpty());
	EXPECT_THAT(secondCell->getNeighbors(), testing::IsEmpty());
}

TEST_F(CellAttributeTest, GivenCellWithAllNeighbors_WhenGetNeighbors_ThenReturnsVectorWithAllNeighbors) {
	CustomSetUp({0, 0}, {0, 1});
	
	std::array<Cell*, 4> directions {};
	directions[0] = secondCell.get();
	directions[1] = std::make_unique<Cell>(-1, 0).get();
	directions[2] = std::make_unique<Cell>(0, -1).get();
	directions[3] = std::make_unique<Cell>(1, 0).get();
	
	firstCell->setNorth(directions[0]);
	firstCell->setWest(directions[1]);
	firstCell->setSouth(directions[2]);
	firstCell->setEast(directions[3]);
	
	EXPECT_THAT(firstCell->getNeighbors(), testing::ElementsAreArray(directions));
}

TEST_F(CellAttributeTest, GivenCellWithTwoNeighbors_WhenGetNeighbors_ThenReturnsVectorWithNeighbors) {
	CustomSetUp({0, 0}, {0, 1});
	
	auto thirdCell {std::make_unique<Cell>(-1, 0)};
	
	firstCell->setNorth(secondCell.get());
	firstCell->setWest(thirdCell.get());
	
	EXPECT_THAT(firstCell->getNeighbors(), testing::UnorderedElementsAre(secondCell.get(), thirdCell.get()));
}

TEST_F(CellAttributeTest, GivenTwoCellsWithoutNorthCell_WhenGetNorth_ThenReturnsNullptr) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getNorth(), testing::IsNull());
	EXPECT_THAT(secondCell->getNorth(), testing::IsNull());
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenGetWestWithoutWestCell_ThenReturnsNullptr) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getWest(), testing::IsNull());
	EXPECT_THAT(secondCell->getWest(), testing::IsNull());
}

TEST_F(CellAttributeTest, GivenTwoCellsWithoutSouthCell_WhenGetSouth_ThenReturnsNullptr) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getSouth(), testing::IsNull());
	EXPECT_THAT(secondCell->getSouth(), testing::IsNull());
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenGetEastWithoutEastCell_ThenReturnsNullptr) {
	CustomSetUp({0, 0}, {0, 1});
	
	EXPECT_THAT(firstCell->getEast(), testing::IsNull());
	EXPECT_THAT(secondCell->getEast(), testing::IsNull());
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenSetNorth_ThenSecondCellBecomesNorthNeighborOfFirstCell) {
	CustomSetUp({0, 0}, {0, 1});
	
	firstCell->setNorth(secondCell.get());
	
	EXPECT_THAT(firstCell->getNorth(), testing::Eq(secondCell.get()));
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenSetWest_ThenSecondCellBecomesWestNeighborOfFirstCell) {
	CustomSetUp({0, 0}, {-1, 0});
	
	firstCell->setWest(secondCell.get());
	
	EXPECT_THAT(firstCell->getWest(), testing::Eq(secondCell.get()));
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenSetSouth_ThenSecondCellBecomesSouthNeighborOfFirstCell) {
	CustomSetUp({0, 0}, {0, -1});
	
	firstCell->setSouth(secondCell.get());
	
	EXPECT_THAT(firstCell->getSouth(), testing::Eq(secondCell.get()));
}

TEST_F(CellAttributeTest, GivenTwoCells_WhenSetEast_ThenSecondCellBecomesEastNeighborOfFirstCell) {
	CustomSetUp({0, 0}, {1, 0});
	
	firstCell->setEast(secondCell.get());
	
	EXPECT_THAT(firstCell->getEast(), testing::Eq(secondCell.get()));
}
}