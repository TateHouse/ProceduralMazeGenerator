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

TEST_F(InMemoryCommandRepositoryTest,
       GivenInMemoryCommandRepository_WhenExecuteGridCommandWithoutParameter_ThenGridIsGeneratedWithDefaultSize) {
    const std::string name {"grid"};
    const auto parameters {std::unordered_map<std::string, std::string> {}};

    commandRepository.execute(name, parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(10));
    EXPECT_THAT(height, testing::Eq(10));
}

TEST_F(InMemoryCommandRepositoryTest,
       GivenInMemoryCommandRepository_WhenExecuteGridCommandWithParameterButWithoutParameterValue_ThenGridIsGeneratedWithDefaultSize) {
    const std::string name {"grid"};
    const auto parameters {std::unordered_map<std::string, std::string> {{"-s", ""}}};

    commandRepository.execute(name, parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(10));
    EXPECT_THAT(height, testing::Eq(10));
}

TEST_F(InMemoryCommandRepositoryTest,
       GivenInMemoryCommandRepository_WhenExecuteGridCommandWithParameterAndParameterValue_ThenGridIsGeneratedWithParameterValue) {
    const std::string name {"grid"};
    const auto parameters {std::unordered_map<std::string, std::string> {{"-s", "20"}}};

    commandRepository.execute(name, parameters);

    const auto [width, height] {context.getGrid()->getSize()};

    EXPECT_THAT(width, testing::Eq(20));
    EXPECT_THAT(height, testing::Eq(20));
}
}