#include "Commands/ExportCommand.hpp"

#include <sstream>
#include <stdexcept>

#include "Commands/CommandParametersUtility.hpp"
#include "ImageVisualizer.hpp"

namespace Console {
ExportCommand::ExportCommand(Context& context) noexcept: Command {context} {

}

void ExportCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
    const auto* const grid {context.getGrid()};
    if (grid == nullptr) {
        throw std::runtime_error {"A grid must be generated before it can be exported"};
    }

    try {
        if (parameters.empty()) {
            throw std::invalid_argument {"No parameters were provided"};
        }

        const auto fileName {CommandParametersUtility::getParameterValue(parameters, "-f")};

        if (fileName.contains('.') || fileName.contains('/') || fileName.contains('\\')) {
            throw std::invalid_argument {"The file name must not contain a file extension or a path"};
        }

        const auto filePath {std::filesystem::path {"Images/" + fileName + ".png"}};
        const auto cellSize {std::stoi(CommandParametersUtility::getParameterValue(parameters, "-cs"))};
        const auto borderSize {std::stoi(CommandParametersUtility::getParameterValue(parameters, "-bs"))};

        auto imageVisualizerBuilder {Core::ImageVisualizer::create(grid, filePath)};
        imageVisualizerBuilder.setCellSize(cellSize);
        imageVisualizerBuilder.setBorderSize(borderSize);
        imageVisualizerBuilder.build()->visualize();
    } catch (const std::invalid_argument& exception) {
        std::cout << exception.what() << '\n';
    }
}

std::string ExportCommand::getName() const noexcept {
    return "export";
}

std::string ExportCommand::getDescription() const noexcept {
    std::ostringstream descriptionStream {};

    descriptionStream
            << "\tExports a grid, modified or unmodified, to a PNG image. All images are exported to the 'Images' folder.\n"
            << "\tThe grid must be generated before it can be exported.\n\n";
    descriptionStream << "\tParameters (Required):\n"
                      << "\t\t-f: The file name of the exported image. It must not include a file extension or path.\n"
                      << "\t\t-bs: The size of the border that extends around the outside of the grid.\n"
                      << "\t\t-cs: The size of each cell.\n\n";
    descriptionStream << "\tUsage:\n"
                      << "\t\t" << getName() << " -f <file name> -bs <border size> -cs <cell size>\n\n";
    descriptionStream << "\tExample:\n"
                      << "\t\t" << getName() << " -f Test -bs 1 -cs 10\n"
                                             << "\t\tThis will export the grid, to 'Images/Test.png' with a border size of 1 and a cell size of 10.";

    return descriptionStream.str();
}
}