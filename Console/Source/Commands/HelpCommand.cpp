#include "Commands/HelpCommand.hpp"

#include <iostream>

namespace Console {
HelpCommand::HelpCommand(Console::Context& context) noexcept:
        Command {context} {

}

void HelpCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    std::cout << "====================================================" << '\n';
    for (const auto& [name, description] : commands) {
        std::cout << name << ": " << description << '\n';
    }
    std::cout << "====================================================" << '\n';
}

std::string HelpCommand::getName() const noexcept {
    return "help";
}

std::string HelpCommand::getDescription() const noexcept {
    return "Displays all available commands and their descriptions.";
}

void HelpCommand::setCommands(const std::map<std::string, std::string>& commands) noexcept {
    this->commands = commands;
}
}