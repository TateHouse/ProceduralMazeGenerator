#include <gmock/gmock.h>

#include <memory>

#include "Commands/InMemoryCommandRepository.hpp"
#include "Console/MockCommand.hpp"
#include "Context.hpp"

namespace Console::Test {
class InMemoryCommandRepositoryTest : public ::testing::Test {
public:
    InMemoryCommandRepositoryTest() noexcept = default;
    virtual ~InMemoryCommandRepositoryTest() noexcept override = default;

protected:
    Context context {};
    InMemoryCommandRepository commandRepository {context};
};

TEST_F(InMemoryCommandRepositoryTest, GivenCommandName_WhenExecute_ThenCommandIsExecuted) {
    auto mockCommand {std::make_unique<MockCommand>(context)};
    const auto parameters {std::unordered_map<std::string, std::string> {}};

    EXPECT_CALL(*mockCommand, getName()).WillRepeatedly(testing::Return("test"));
    EXPECT_CALL(*mockCommand, execute(parameters)).Times(1);

    commandRepository.add(std::move(mockCommand));
    commandRepository.execute("test", {});
}

TEST_F(InMemoryCommandRepositoryTest, GivenNonExistantCommandName_WhenExecute_ThenThrowsInvalidArgument) {
    EXPECT_THROW(commandRepository.execute("test", {}), std::invalid_argument);
}
}