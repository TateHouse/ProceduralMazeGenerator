#include "Commands/GridCommand.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Commands/CommandParametersUtility.hpp"

namespace Console {
GridCommand::GridCommand(Console::Context& context) noexcept: Command {context} {

}

void GridCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    try {
        if (parameters.empty()) {
            throw std::invalid_argument {
                    "A new grid with the default size of " + std::to_string(GridCommand::defaultGridSize) +
                    " has been generated."};
        }

        const auto size {std::stoi(CommandParametersUtility::getParameterValue(parameters, "-s"))};
        context.setGrid(size);
        std::cout << "A new grid with a size of " << size << " has been generated." << '\n';
    } catch (const std::invalid_argument& exception) {
        context.setGrid(GridCommand::defaultGridSize);
        std::cout << exception.what() << '\n';
    }
}

std::string GridCommand::getName() const noexcept {
    return "grid";
}

std::string GridCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};

    descriptionStream << "\tGenerates a grid. The default size is " << GridCommand::defaultGridSize << ".\n\n";
    descriptionStream << "\tParameters (Optional):\n"
                      << "\t\t-s: The size of the grid.\n\n";
    descriptionStream << "\tUsage:\n"
                      << "\t\t" << getName() << " -s <size>\n\n";
    descriptionStream << "\tExample:\n"
                      << "\t\t" << getName() << " -s 20\n"
                                             << "\t\tThis will generate a grid with a size of 20.";

    return descriptionStream.str();
}
}