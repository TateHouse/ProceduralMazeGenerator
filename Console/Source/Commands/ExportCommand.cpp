#include "Commands/ExportCommand.hpp"

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
    return "Export the current grid, modified or unmodified by a maze generation algorithm, to an image file";
}
}