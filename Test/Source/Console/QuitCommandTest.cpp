#include <gmock/gmock.h>

#include "Commands/QuitCommand.hpp"
#include "Context.hpp"

namespace Console::Test {
class QuitCommandTest : public ::testing::Test {
public:
    QuitCommandTest() noexcept = default;
	~QuitCommandTest() noexcept override = default;

protected:
    Context context {};
    QuitCommand command {context};
};

TEST_F(QuitCommandTest, GivenNoParameter_WhenExecute_ThenApplicationIsNotRunning) {
    const auto parameters {std::unordered_map<std::string, std::string> {}};

    command.execute(parameters);

    EXPECT_THAT(context.getIsRunning(), testing::IsFalse());
}

TEST_F(QuitCommandTest, GivenParameters_WhenExecute_ThenThrowsInvalidArgument) {
    const auto parameters {std::unordered_map<std::string, std::string> {{"-f", "value"}}};

    EXPECT_THROW(command.execute(parameters), std::invalid_argument);
}
}