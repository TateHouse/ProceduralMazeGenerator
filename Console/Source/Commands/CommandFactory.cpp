#include "Commands/CommandFactory.hpp"

#include "Commands/ExportCommand.hpp"
#include "Commands/GridCommand.hpp"
#include "Commands/HelpCommand.hpp"
#include "Commands/MazeCommand.hpp"
#include "Commands/QuitCommand.hpp"

namespace Console {
CommandFactory::CommandFactory(Console::Context& context) noexcept: context {context} {
    const auto exportCommand {std::make_unique<ExportCommand>(context)};
    const auto gridCommand {std::make_unique<GridCommand>(context)};
    const auto helpCommand {std::make_unique<HelpCommand>(context)};
    const auto mazeCommand {std::make_unique<MazeCommand>(context)};
    const auto quitCommand {std::make_unique<QuitCommand>(context)};

    std::map<std::string, std::string> commandNamesAndDescriptions {};
    commandNamesAndDescriptions.try_emplace(exportCommand->getName(), exportCommand->getDescription());
    commandNamesAndDescriptions.try_emplace(gridCommand->getName(), gridCommand->getDescription());
    commandNamesAndDescriptions.try_emplace(helpCommand->getName(), helpCommand->getDescription());
    commandNamesAndDescriptions.try_emplace(mazeCommand->getName(), mazeCommand->getDescription());
    commandNamesAndDescriptions.try_emplace(quitCommand->getName(), quitCommand->getDescription());

    commands.try_emplace(exportCommand->getName(), [](Context& context) {
        return std::make_unique<ExportCommand>(context);
    });

    commands.try_emplace(gridCommand->getName(), [](Context& context) {
        return std::make_unique<GridCommand>(context);
    });

    commands.try_emplace(helpCommand->getName(), [commandNamesAndDescriptions](Context& context) {
        auto command {std::make_unique<HelpCommand>(context)};
        command->setCommands(commandNamesAndDescriptions);
        return command;
    });

    commands.try_emplace(mazeCommand->getName(), [](Context& context) {
        return std::make_unique<MazeCommand>(context);
    });

    commands.try_emplace(quitCommand->getName(), [](Context& context) {
        return std::make_unique<QuitCommand>(context);
    });
}

std::unique_ptr<Command> CommandFactory::create(const std::string& name) const noexcept {
    const auto iterator {commands.find(name)};

    return iterator != commands.end() ? iterator->second(context) : nullptr;
}
}