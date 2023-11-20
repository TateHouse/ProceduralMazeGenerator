#include <gmock/gmock.h>

#include <memory>
#include <optional>

#include "WilsonsMazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Core::Test {
class WilsonsMazeGeneratorTest : public testing::Test {
public:
	WilsonsMazeGeneratorTest() noexcept {
		grid->initialize();
		mazeGenerator->generate(grid.get(), std::nullopt);
	}
	
	virtual ~WilsonsMazeGeneratorTest() noexcept = default;

protected:
	std::unique_ptr<Grid> grid {std::make_unique<SquareGrid>(5)};
	std::unique_ptr<MazeGenerator> mazeGenerator {std::make_unique<WilsonsMazeGenerator>()};
	const int width {grid->getSize().first};
	const int height {grid->getSize().second};
};

TEST_F(WilsonsMazeGeneratorTest, GivenSquareGrid_WhenGenerate_ThenEveryCellHasBetweenOneAndFourLinks) {
	for (std::size_t x {0}; x < width; ++x) {
		for (std::size_t y {0}; y < height; ++y) {
			const auto xPosition {static_cast<int>(x)};
			const auto yPosition {static_cast<int>(y)};
			const auto* const cell {(*grid)[{xPosition, yPosition}]};
			const auto& links {cell->getLinks()};
			
			EXPECT_THAT(links, testing::SizeIs(testing::AnyOf(1, 2, 3, 4)));
		}
	}
}
}