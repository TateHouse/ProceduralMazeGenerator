#include "Commands/QuitCommand.hpp"

#include <sstream>
#include <stdexcept>

namespace Console {
QuitCommand::QuitCommand(Console::Context& context) noexcept: Command {context} {

}

void QuitCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    if (!parameters.empty()) {
        throw std::invalid_argument {"Quit command does not accept parameters"};
    }

    context.setIsNotRunning();
}

std::string QuitCommand::getName() const noexcept {
    return "quit";
}

std::string QuitCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};

    descriptionStream << "\tQuits the application.\n\n";

    descriptionStream << "\tUsage:\n"
                      << "\t\t" << getName();

    return descriptionStream.str();
}
}