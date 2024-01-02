#include "Commands/HelpCommand.hpp"

#include <iostream>
#include <sstream>

#include "Commands/CommandParametersUtility.hpp"

namespace Console {
HelpCommand::HelpCommand(Console::Context& context) noexcept:
        Command {context} {

}

void HelpCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    if (parameters.empty()) {
        std::cout << "====================================================" << '\n';

        for (const auto& [name, description] : commands) {
            std::cout << name << ':' << '\n';
            std::cout << description << '\n';
        }

        std::cout << "====================================================" << '\n';
        return;
    }

    const auto commandName {CommandParametersUtility::getParameterValue(parameters, "-c")};
    const auto iterator {commands.find(commandName)};
    if (iterator == commands.end()) {
        std::cout << "The specified command does not exist" << '\n';
        return;
    }

    std::cout << "====================================================" << '\n';
    std::cout << iterator->first << ':' << '\n';
    std::cout << iterator->second << '\n';
    std::cout << "====================================================" << '\n';
}

std::string HelpCommand::getName() const noexcept {
    return "help";
}

std::string HelpCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};
    descriptionStream << "\tDisplays the name and description of all commands.\n\n";
    descriptionStream << "\tParameters (Optional):\n"
                      << "\t\t-c <command name>\n"
                      << "\t\t\tDisplays the name and description of the specified command.\n\n";
    descriptionStream << "\tUsage:\n"
                      << "\t\thelp\n"
                      << "\t\thelp -c <command name>\n\n";
    descriptionStream << "\tExamples:\n"
                      << "\t\thelp\n"
                      << "\t\tThis will display the name and description of all commands.\n\n"
                      << "\t\thelp -c maze\n\n"
                      << "\t\tThis will display the name and description of the maze command.";

    return descriptionStream.str();
}

void HelpCommand::setCommands(const std::map<std::string, std::string>& commands) noexcept {
    this->commands = commands;
}
}