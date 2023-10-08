#include <gmock/gmock.h>

#include <memory>

#include "BinaryTreeMazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Core::Test {
class MazeGeneratorTest : public ::testing::Test {
public:
	MazeGeneratorTest() noexcept {
		grid->initialize();
	}
	
	virtual ~MazeGeneratorTest() noexcept = default;

protected:
	std::unique_ptr<Grid> grid {std::make_unique<SquareGrid<5>>()};
	std::unique_ptr<MazeGenerator> mazeGenerator {std::make_unique<BinaryTreeMazeGenerator>()};
};

TEST_F(MazeGeneratorTest, GivenMazeGeneratorThatDoesNotContainSeed_WhenGetSeed_ThenReturnsNullopt) {
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithoutSeed_ThenUsesRandomSeed) {
	mazeGenerator->generate(grid.get(), nullptr);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Ne(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithSeed_ThenUsesSeed) {
	const unsigned long long seed {123456789};
	mazeGenerator->generate(grid.get(), &seed);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(seed));
}
}