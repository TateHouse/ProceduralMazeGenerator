#include "Commands/CommandFactory.hpp"

#include "Commands/ExportCommand.hpp"
#include "Commands/GridCommand.hpp"
#include "Commands/MazeCommand.hpp"
#include "Commands/QuitCommand.hpp"

namespace Console {
CommandFactory::CommandFactory(Console::Context& context) noexcept: context {context} {
    const auto exportCommand {std::make_unique<ExportCommand>(context)};
    const auto gridCommand {std::make_unique<GridCommand>(context)};
    const auto mazeCommand {std::make_unique<MazeCommand>(context)};
    const auto quitCommand {std::make_unique<QuitCommand>(context)};

    commands.try_emplace(exportCommand->getName(), [](Context& context) {
        return std::make_unique<ExportCommand>(context);
    });

    commands.try_emplace(gridCommand->getName(), [](Context& context) {
        return std::make_unique<GridCommand>(context);
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