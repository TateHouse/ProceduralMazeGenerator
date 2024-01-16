#include "Commands/VisualizeCommand.hpp"

#include <sstream>
#include <stdexcept>

#include "Commands/CommandParametersUtility.hpp"
#include "ConsoleGridVisualizer.hpp"
#include "ConsoleMazeVisualizer.hpp"

namespace Console {
VisualizeCommand::VisualizeCommand(Context& context) noexcept: Command {context} {

}

void VisualizeCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
	try {
		if (parameters.empty()) {
			throw std::invalid_argument {"No parameters were provided"};
		}
		
		auto* grid {context.getGrid()};
		if (grid == nullptr) {
			throw std::runtime_error {"A grid must be generated before it can be visualized"};
		}
		
		const auto visualizationType {CommandParametersUtility::getParameterValue(parameters, "-t")};
		std::unique_ptr<Core::GridVisualizer> consoleGridVisualizer {nullptr};
		
		if (visualizationType == "grid") {
			consoleGridVisualizer = std::make_unique<ConsoleGridVisualizer>(grid);
		} else if (visualizationType == "maze") {
			consoleGridVisualizer = std::make_unique<ConsoleMazeVisualizer>(grid);
		} else {
			throw std::invalid_argument {"The visualization type must be either 'grid' or 'maze'"};
		}
		
		consoleGridVisualizer->visualize();
	} catch (const std::exception& exception) {
		throw std::invalid_argument {exception.what()};
	}
}

std::string VisualizeCommand::getName() const noexcept {
	return "visualize";
}

std::string VisualizeCommand::getDescription() const noexcept {
	std::ostringstream descriptionStream {};
	descriptionStream << "\tVisualizes the generated grid or maze in the console using ASCII.\n\n";
	descriptionStream << "\tParameters (Required):\n"
	                  << "\t\t-t: The type of visualization to use. Valid values are 'grid' and 'maze'.\n\n";
	descriptionStream << "\tUsage:\n"
	                  << "\t\t" << getName() << " -t <visualization type>\n\n";
	descriptionStream << "\tExample:\n"
	                  << "\t\t" << getName() << " -t grid\n"
	                  << "\t\tThis will visualize the generated grid in the console using ASCII.\n\n"
	                  << "\t\t" << getName() << " -t maze\n"
	                  << "\t\tThis will visualize the generated maze in the console using ASCII.\n\n";
	
	return descriptionStream.str();
}
}