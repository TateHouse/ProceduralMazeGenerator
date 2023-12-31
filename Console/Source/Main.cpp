#include <iostream>
#include <string>

#include "Commands/CommandFactory.hpp"
#include "Commands/CommandParser.hpp"
#include "Commands/InMemoryCommandRepository.hpp"
#include "Context.hpp"

void initializeCommands(Console::Context& context, Console::InMemoryCommandRepository& commandRepository) {
	Console::CommandFactory commandFactory {context};
	commandRepository.add(commandFactory.create("export"));
	commandRepository.add(commandFactory.create("grid"));
	commandRepository.add(commandFactory.create("help"));
	commandRepository.add(commandFactory.create("maze"));
	commandRepository.add(commandFactory.create("quit"));
	commandRepository.add(commandFactory.create("visualize"));
}

int main(int argc, char* argv[]) {
	Console::Context context;
	Console::InMemoryCommandRepository commandRepository {context};
	initializeCommands(context, commandRepository);
	
	std::string input {};
	while (context.getIsRunning()) {
		try {
			std::getline(std::cin, input);
			const auto parsedCommand {Console::CommandParser::parse(input)};
			commandRepository.execute(parsedCommand.getName(), parsedCommand.getParameters());
		} catch (const std::runtime_error& exception) {
			std::cerr << exception.what() << '\n';
		} catch (const std::invalid_argument& exception) {
			std::cerr << exception.what() << '\n';
		}
	}
	
	return 0;
}