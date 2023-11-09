#include "Commands/GridCommand.hpp"

#include <stdexcept>

namespace Console {
GridCommand::GridCommand(Console::Context& context) noexcept: Command {context} {

}

void GridCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    try {
        if (parameters.empty()) {
            throw std::invalid_argument {"Size parameter is empty, the default size will be used."};
        }

        auto iterator {parameters.find("-s")};
        if (iterator == parameters.end()) {
            throw std::invalid_argument {"Size parameter is empty, the default size will be used."};
        }

        const auto size {std::stoi(iterator->second)};
        if (size < 1) {
            throw std::invalid_argument {"Size parameter is invalid, the default size will be used."};
        }

        context.setGrid(size);
    } catch (const std::invalid_argument&) {
        context.setGrid(GridCommand::defaultGridSize);
    }
}

std::string GridCommand::getName() const noexcept {
    return "grid";
}

std::string GridCommand::getDescription() const noexcept {
    return "Generates a square grid.";
}
}