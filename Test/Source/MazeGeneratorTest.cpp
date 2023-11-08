#include <gmock/gmock.h>

#include <memory>
#include <optional>

#include "FakeMazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Core::Test {
class MazeGeneratorTest : public ::testing::Test {
public:
	MazeGeneratorTest() noexcept {
		grid->initialize();
	}
	
	virtual ~MazeGeneratorTest() noexcept = default;

protected:
    std::unique_ptr<Grid> grid {std::make_unique<SquareGrid>(5)};
	std::unique_ptr<MazeGenerator> mazeGenerator {std::make_unique<FakeMazeGenerator>()};
};

TEST_F(MazeGeneratorTest,
       GivenMazeGenerator_WhenGetMazeGenerationAlgorithmName_ThenReturnsMazeGenerationAlgorithmName) {
	EXPECT_THAT(mazeGenerator->getAlgorithmName(), testing::Eq("Mock Maze Generator"));
}

TEST_F(MazeGeneratorTest, GivenMazeGeneratorThatDoesNotContainSeed_WhenGetSeed_ThenReturnsNullopt) {
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithoutSeed_ThenSetsRandomSeed) {
    mazeGenerator->generate(grid.get(), std::nullopt);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Ne(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithSeed_ThenSetsSeed) {
	const unsigned long long seed {100};
    mazeGenerator->generate(grid.get(), seed);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(seed));
}
}