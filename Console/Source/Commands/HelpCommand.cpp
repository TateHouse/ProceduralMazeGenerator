#include "Commands/HelpCommand.hpp"

#include <iostream>
#include <sstream>

namespace Console {
HelpCommand::HelpCommand(Console::Context& context) noexcept:
        Command {context} {

}

void HelpCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    std::cout << "====================================================" << '\n';
    for (const auto& [name, description] : commands) {
        std::cout << name << ':' << '\n';
        std::cout << description << '\n';
    }
    std::cout << "====================================================" << '\n';
}

std::string HelpCommand::getName() const noexcept {
    return "help";
}

std::string HelpCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};

    descriptionStream << "\tDisplays the name and description of all commands.\n\n";

    descriptionStream << "\tUsage:\n"
                      << "\t\t" << getName() << '\n';

    return descriptionStream.str();
}

void HelpCommand::setCommands(const std::map<std::string, std::string>& commands) noexcept {
    this->commands = commands;
}
}