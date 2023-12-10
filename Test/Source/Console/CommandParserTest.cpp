#include <gmock/gmock.h>

#include <vector>

#include "Commands/CommandParser.hpp"

namespace Console::Test {
class CommandParserTest : public testing::Test {
public:
    CommandParserTest() noexcept = default;
    ~CommandParserTest() noexcept override = default;
};

TEST_F(CommandParserTest, GivenEmptyString_WhenParse_ThenThrowsInvalidArgument) {
    EXPECT_THROW(CommandParser::parse(""), std::invalid_argument);
}

TEST_F(CommandParserTest, GivenWhitespaceString_WhenParse_ThenThrowsInvalidArgument) {
    EXPECT_THROW(CommandParser::parse(" "), std::invalid_argument);
}

TEST_F(CommandParserTest, GivenStringContainingCommandWithoutParameterDelimiter_WhenParse_ThenThrowsInvalidArgument) {
    EXPECT_THROW(CommandParser::parse("quit f"), std::invalid_argument);
}

TEST_F(CommandParserTest,
       GivenStringContainingCommandWithoutParameters_WhenParse_ThenReturnsParsedCommandInputWithoutParametersOrParameterValues) {
    const std::string command {"quit"};
    const auto parsedCommandInput {CommandParser::parse(command)};

    EXPECT_THAT(parsedCommandInput.getName(), testing::Eq(command));
    EXPECT_THAT(parsedCommandInput.getParameters(), testing::IsEmpty());
}

TEST_F(CommandParserTest,
       GivenStringContainingCommandWithParametersButWithoutParameterValues_WhenParse_ThenReturnsParsedCommandInputWithParametersButWithoutParameterValues) {
    const std::string command {"quit -f -s"};
    const auto parsedCommandInput {CommandParser::parse(command)};

    EXPECT_THAT(parsedCommandInput.getName(), testing::Eq("quit"));

    const auto parameters {parsedCommandInput.getParameters()};
	for (const auto& [key, value] : parameters) {
		ASSERT_THAT(key, testing::StartsWith("-"));
		EXPECT_THAT(key, testing::AnyOf(testing::Eq("-f"), testing::Eq("-s")));
		EXPECT_THAT(value, testing::IsEmpty());
	}
}

TEST_F(CommandParserTest,
       GivenStringContainingCommandWithParametersAndParameterValues_WhenParse_ThenReturnsParsedCommandInputWithParametersAndParameterValues) {
    const std::string command {"quit -f value -s 50"};
    const auto parsedCommandInput {CommandParser::parse(command)};

    EXPECT_THAT(parsedCommandInput.getName(), testing::Eq("quit"));

    const auto& parameters {parsedCommandInput.getParameters()};
	
	for (const auto& [key, value] : parameters) {
		ASSERT_THAT(key, testing::StartsWith("-"));
		EXPECT_THAT(key, testing::AnyOf(testing::Eq("-f"), testing::Eq("-s")));
		EXPECT_THAT(value, testing::AnyOf(testing::Eq("value"), testing::Eq("50")));
	}
}
}