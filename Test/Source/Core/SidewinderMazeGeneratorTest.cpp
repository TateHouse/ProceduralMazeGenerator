#include <gmock/gmock.h>

#include <memory>
#include <optional>

#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"

namespace Core::Test {
class SidewinderMazeGeneratorTest : public testing::Test {
public:
    SidewinderMazeGeneratorTest() noexcept {
        grid->initialize();
        mazeGenerator->generate(grid.get(), std::nullopt);
    }

    ~SidewinderMazeGeneratorTest() noexcept override = default;

protected:
    std::unique_ptr<Grid> grid {std::make_unique<SquareGrid>(5)};
    std::unique_ptr<MazeGenerator> mazeGenerator {std::make_unique<SidewinderMazeGenerator>()};
    const int width {grid->getSize().first};
    const int height {grid->getSize().second};
};

TEST_F(SidewinderMazeGeneratorTest,
       GivenSidewinderMazeGenerator_WhenGenerate_ThenNorthmostCellsAreLinkedToCreateHorizontalPassgae) {
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

TEST_F(SidewinderMazeGeneratorTest, GivenSidewinderMazeGenerator_WhenGenerate_ThenEveryCellHasBetweenOneAndFourLinks) {
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