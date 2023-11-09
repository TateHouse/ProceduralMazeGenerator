#include "Commands/InMemoryCommandRepository.hpp"

#include "Commands/GridCommand.hpp"
#include "Commands/QuitCommand.hpp"

#include <stdexcept>

namespace Console {
InMemoryCommandRepository::InMemoryCommandRepository(Console::Context& context) noexcept: CommandRepository {context} {
    auto gridCommand {std::make_unique<GridCommand>(context)};
    auto quitCommand {std::make_unique<QuitCommand>(context)};

    commands.try_emplace(gridCommand->getName(), std::move(gridCommand));
    commands.try_emplace(quitCommand->getName(), std::move(quitCommand));
}

void InMemoryCommandRepository::execute(const std::string_view command,
                                        const std::unordered_map<std::string, std::string>& parameters) {
    auto iterator {commands.find(command.data())};

    if (iterator == commands.end()) {
        throw std::invalid_argument {"Command not found"};
    }

    iterator->second->execute(parameters);
}
}