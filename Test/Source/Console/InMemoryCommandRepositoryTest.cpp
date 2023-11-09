#include <gmock/gmock.h>

#include <memory>

#include "Commands/InMemoryCommandRepository.hpp"
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

TEST_F(InMemoryCommandRepositoryTest,
       GivenInMemoryCommandRepository_WhenExecuteQuitCommand_ThenApplicationIsNotRunning) {
    const std::string name {"quit"};
    const auto parameters {std::unordered_map<std::string, std::string> {}};

    commandRepository.execute(name, parameters);

    EXPECT_THAT(context.getIsRunning(), testing::IsFalse());
}
}