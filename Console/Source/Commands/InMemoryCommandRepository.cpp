#include "Commands/InMemoryCommandRepository.hpp"

#include <stdexcept>

namespace Console {
InMemoryCommandRepository::InMemoryCommandRepository(Console::Context& context) noexcept: CommandRepository {context} {

}

void InMemoryCommandRepository::add(std::unique_ptr<Command> command) {
    const auto name {command->getName()};
    commands.try_emplace(name, std::move(command));
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