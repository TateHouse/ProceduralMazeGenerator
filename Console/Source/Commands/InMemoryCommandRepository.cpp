#include "Commands/InMemoryCommandRepository.hpp"

#include <stdexcept>

namespace Console {
InMemoryCommandRepository::InMemoryCommandRepository(Console::Context& context) noexcept: CommandRepository {context} {

}

void InMemoryCommandRepository::execute(const std::string_view command) {
    auto iterator {commands.find(command.data())};

    if (iterator == commands.end()) {
        throw std::invalid_argument {"Command not found"};
    }

    iterator->second->execute();
}
}