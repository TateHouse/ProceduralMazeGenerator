#include <gmock/gmock.h>

#include "Cell.hpp"

namespace Core::Test {
class CellLinkingTest : public testing::Test {
public:
	CellLinkingTest() noexcept = default;
	~CellLinkingTest() noexcept override = default;

protected:
	Cell firstCell {0, 0};
	Cell secondCell {0, 1};
};

TEST_F(CellLinkingTest, GivenTwoUnlinknedCells_WhenLink_ThenTheTwoCellsAreLinked) {
	firstCell.link(&secondCell);
	
	EXPECT_THAT(firstCell.getLinks(), testing::Contains(&secondCell));
	EXPECT_THAT(secondCell.getLinks(), testing::Contains(&firstCell));
}

TEST_F(CellLinkingTest, GivenTwoLinkedCells_WhenUnlink_ThenTheTwoCellsAreUnlinked) {
	firstCell.link(&secondCell);
	
	firstCell.unlink(&secondCell);
	
	EXPECT_THAT(firstCell.getLinks(), testing::Not(testing::Contains(&secondCell)));
	EXPECT_THAT(secondCell.getLinks(), testing::Not(testing::Contains(&firstCell)));
}

TEST_F(CellLinkingTest, GivenTwoUnlinkedCells_WhenCheckIfLinked_ThenReturnsFalse) {
	EXPECT_THAT(firstCell.isLinked(&secondCell), testing::IsFalse());
	EXPECT_THAT(secondCell.isLinked(&firstCell), testing::IsFalse());
}

TEST_F(CellLinkingTest, GivenTwoLinkedCells_WhenCheckIfLinked_ThenReturnsTrue) {
	firstCell.link(&secondCell);
	
	EXPECT_THAT(firstCell.isLinked(&secondCell), testing::IsTrue());
	EXPECT_THAT(secondCell.isLinked(&firstCell), testing::IsTrue());
}
}