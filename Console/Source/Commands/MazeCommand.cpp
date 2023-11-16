#include "Commands/MazeCommand.hpp"

#include <iostream>
#include <sstream>

#include "Commands/CommandParametersUtility.hpp"
#include "AldousBroderMazeGenerator.hpp"
#include "BinaryTreeMazeGenerator.hpp"
#include "SidewinderMazeGenerator.hpp"

namespace Console {
MazeCommand::MazeCommand(Console::Context& context) noexcept: Command {context} {
	mazeGenerators.emplace_back(std::make_unique<Core::AldousBroderMazeGenerator>());
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

        std::cout << "Modified the grid using the " << algorithm << " algorithm." << '\n';
    } catch (const std::invalid_argument& exception) {
        std::cout << exception.what() << '\n';
    }
}

std::string MazeCommand::getName() const noexcept {
    return "maze";
}

std::string MazeCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};

    descriptionStream
            << "\tModifies a grid by applying a maze generation algorithm to it. The grid must be generated before it can be modified.\n\n";

    descriptionStream << "\tParameters (Required):\n"
                      << "\t\t-a: The algorithm to use. The available algorithms are:\n";

    for (const auto& mazeGenerator : mazeGenerators) {
        descriptionStream << "\t\t\t" << mazeGenerator->getAlgorithmName() << '\n';
    }

    descriptionStream << "\n";

    descriptionStream << "\tParameters (Optional):\n"
                      << "\t\t-s: An unsigned integer to use as the seed. If no seed is provided, a random seed will be used.\n\n";

    descriptionStream << "\tUsage:\n"
                      << "\t\t" << getName() << " -a <algorithm> -s <seed>\n\n";

    descriptionStream << "\tExample:\n"
                      << "\t\t" << getName() << " -a BinaryTree -s 1234\n"
                      << "\t\tThis will modify the grid using the binary tree algorithm with a seed of 1234.\n\n"
                      << "\t\t" << getName() << "-a Sidewinder\n"
                      << "\t\tThis will modify the grid using the sidewinder algorithm with a random seed.";

    return descriptionStream.str();
}
}