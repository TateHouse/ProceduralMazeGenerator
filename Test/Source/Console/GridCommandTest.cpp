#include <gmock/gmock.h>

#include "Commands/GridCommand.hpp"
#include "Context.hpp"

namespace Console::Test {
class GridCommandTest : public ::testing::Test {
public:
    GridCommandTest() noexcept = default;
    virtual ~GridCommandTest() noexcept override = default;

protected:
    Context context {};
    GridCommand command {context};
};

TEST_F(GridCommandTest, GivenNoParameter_WhenExecute_ThenGridIsGeneratedWithDefaultSize) {
    const auto parameters {std::unordered_map<std::string, std::string> {}};

    command.execute(parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(10));
    EXPECT_THAT(height, testing::Eq(10));
}

TEST_F(GridCommandTest, GivenParameterButWithoutParameterValue_WhenExecute_ThenGridIsGeneratedWithDefaultSize) {
    const auto parameters {std::unordered_map<std::string, std::string> {{"-s", ""}}};

    command.execute(parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(10));
    EXPECT_THAT(height, testing::Eq(10));
}

TEST_F(GridCommandTest, GivenParameterAndParameterValue_WhenExecute_ThenGridIsGeneratedWithParameterValue) {
    const auto parameters {std::unordered_map<std::string, std::string> {{"-s", "20"}}};

    command.execute(parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(20));
    EXPECT_THAT(height, testing::Eq(20));
}
}