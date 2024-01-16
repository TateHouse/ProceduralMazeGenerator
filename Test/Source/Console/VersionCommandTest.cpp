#include <gmock/gmock.h>

#include <sstream>

#include "Commands/VersionCommand.hpp"

namespace Console::Test {
class VersionCommandTest : public ::testing::Test {
public:
	VersionCommandTest() noexcept = default;
	virtual ~VersionCommandTest() noexcept override = default;

protected:
	Context context {};
	VersionCommand command {context};
};

TEST_F(VersionCommandTest, GivenNoParameter_WhenExecute_ThenOutputsVersionToConsole) {
	const auto parameters {std::unordered_map<std::string, std::string> {}};
	std::streambuf* const originalCoutBuffer {std::cout.rdbuf()};
	std::stringstream buffer {};
	std::cout.rdbuf(buffer.rdbuf());
	
	command.execute(parameters);
	
	std::cout.rdbuf(originalCoutBuffer);
	
	EXPECT_THAT(buffer.str(), testing::StrCaseEq("Version: " VERSION "\n"));
}

TEST_F(VersionCommandTest, GivenParameter_WhenExecute_ThenThrowsInvalidArgument) {
	const auto parameters {std::unordered_map<std::string, std::string> {{"-f", "value"}}};
	
	EXPECT_THROW(command.execute(parameters), std::invalid_argument);
}
}