#include <iostream>
#include <string>

#include "Commands/CommandParser.hpp"
#include "Commands/InMemoryCommandRepository.hpp"
#include "Context.hpp"

int main(int argc, char* argv[]) {
    Console::Context context;
    Console::InMemoryCommandRepository commandRepository {context};
    Console::CommandParser commandInterpreter {commandRepository};

    std::string input {};
    while (context.getIsRunning()) {
        try {
            std::cin >> input;
            const auto parsedCommand {commandInterpreter.interpret(input)};
            commandRepository.execute(parsedCommand.getName(), parsedCommand.getParameters());
        } catch (const std::invalid_argument& exception) {
            std::cerr << exception.what() << '\n';
        }
    }

    return 0;
}