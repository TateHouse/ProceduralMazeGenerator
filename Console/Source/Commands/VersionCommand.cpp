#include "Commands/VersionCommand.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace Console {
VersionCommand::VersionCommand(Console::Context& context) noexcept: Command {context} {

}

void VersionCommand::execute(const std::unordered_map<std::string, std::string>& parameters) {
	if (!parameters.empty()) {
		throw std::invalid_argument {"Version command does not accept parameters"};
	}
	
	std::cout << "Version: " << VERSION << '\n';
}

std::string VersionCommand::getName() const noexcept {
	return "version";
}

std::string VersionCommand::getDescription() const noexcept {
	std::ostringstream descriptionStream {};
	descriptionStream << "\tDisplays the project version.\n\n";
	descriptionStream << "\tUsage:\n"
	                  << "\t\t" << getName();
	
	return descriptionStream.str();
}
}