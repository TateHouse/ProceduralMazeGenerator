#include "Console/MockCommand.hpp"

namespace Console::Test {
MockCommand::MockCommand(Console::Context& context) noexcept: Command {context} {

}
}