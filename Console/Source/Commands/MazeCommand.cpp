#include "Commands/MazeCommand.hpp"

#include <iostream>

#include "Commands/CommandParametersUtility.hpp"
#include "BinaryTreeMazeGenerator.hpp"
#include "SidewinderMazeGenerator.hpp"

namespace Console {
MazeCommand::MazeCommand(Console::Context& context) noexcept: Command {context} {
    mazeGenerators.emplace_back(std::make_unique<Core::BinaryTreeMazeGenerator>());
    mazeGenerators.emplace_back(std::make_unique<Core::SidewinderMazeGenerator>());
}

void MazeCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    auto* const grid {context.getGrid()};
    if (grid == nullptr) {
        throw std::runtime_error {"A grid must be generated before it can be modified by a maze generation algorithm"};
    }

    try {
        if (parameters.empty()) {
            throw std::invalid_argument {"No parameters were provided"};
        }

        const auto algorithm {CommandParametersUtility::getParameterValue(parameters, "-a")};
        auto generator {
                std::find_if(mazeGenerators.begin(), mazeGenerators.end(), [&algorithm](const auto& mazeGenerator) {
                    return mazeGenerator->getAlgorithmName() == algorithm;
                })};

        if (generator == mazeGenerators.end()) {
            throw std::invalid_argument {"The specified algorithm does not exist"};
        }

        try {
            const auto seed {std::stoi(CommandParametersUtility::getParameterValue(parameters, "-s"))};
            (*generator)->generate(grid, seed);
        } catch (const std::invalid_argument& exception) {
            (*generator)->generate(grid, std::nullopt);
        }

        std::cout << "Grid modified by " << (*generator)->getAlgorithmName() << '\n';
    } catch (const std::invalid_argument& exception) {
        std::cout << exception.what() << '\n';
    }
}

std::string MazeCommand::getName() const noexcept {
    return "maze";
}

std::string MazeCommand::getDescription() const noexcept {
    return "Modifies a grid to create a maze using a specified algorithm.";
}
}