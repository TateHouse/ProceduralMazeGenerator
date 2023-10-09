#include <gmock/gmock.h>

#include <memory>

#include "MockMazeGenerator.hpp"
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
	std::unique_ptr<MockMazeGenerator> mazeGenerator {std::make_unique<MockMazeGenerator>()};
};

TEST_F(MazeGeneratorTest,
       GivenMazeGenerator_WhenGetMazeGenerationAlgorithmName_ThenReturnsMazeGenerationAlgorithmName) {
	EXPECT_THAT(mazeGenerator->getMazeGenerationAlgorithmName(), testing::Eq("Mock Maze Generator"));
}

TEST_F(MazeGeneratorTest, GivenMazeGeneratorThatDoesNotContainSeed_WhenGetSeed_ThenReturnsNullopt) {
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithoutSeed_ThenUsesRandomSeed) {
	EXPECT_CALL(*mazeGenerator, generate(grid.get(), nullptr)).Times(1).WillOnce([this](const Grid* const grid,
	                                                                                    const unsigned long long*) {
		mazeGenerator->getRandomEngineWrapper(nullptr);
	});
	
	mazeGenerator->generate(grid.get(), nullptr);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Ne(std::nullopt));
}

TEST_F(MazeGeneratorTest, GivenMazeGenerator_WhenGenerateWithSeed_ThenUsesSeed) {
	const unsigned long long seed {123456789};
	
	EXPECT_CALL(*mazeGenerator, generate(grid.get(), &seed)).Times(1).WillOnce([this, &seed](const Grid* const grid,
	                                                                                         const unsigned long long*) {
		mazeGenerator->getRandomEngineWrapper(&seed);
	});
	
	mazeGenerator->generate(grid.get(), &seed);
	
	EXPECT_THAT(mazeGenerator->getSeed(), testing::Eq(seed));
}
}