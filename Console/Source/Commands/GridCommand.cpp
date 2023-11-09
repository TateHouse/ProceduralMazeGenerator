#include "Commands/GridCommand.hpp"

#include <iostream>
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

        if (iterator->second.empty()) {
            throw std::invalid_argument {"Size parameter is empty, the default size will be used."};
        }

        const auto size {std::stoi(iterator->second)};
        if (size < 1) {
            throw std::invalid_argument {"Size parameter is invalid, the default size will be used."};
        }

        context.setGrid(size);
        std::cout << "Grid size set to " << size << '\n';
    } catch (const std::invalid_argument& exception) {
        context.setGrid(GridCommand::defaultGridSize);
        std::cout << exception.what() << '\n';
    }
}

std::string GridCommand::getName() const noexcept {
    return "grid";
}

std::string GridCommand::getDescription() const noexcept {
    return "Generates a square grid.";
}
}