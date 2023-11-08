#include <iostream>
#include <string>

#include "Commands/CommandParser.hpp"
#include "Commands/InMemoryCommandRepository.hpp"
#include "Context.hpp"

int main(int argc, char* argv[]) {
    Console::Context context;
    Console::InMemoryCommandRepository commandRepository {context};

    std::string input {};
    while (context.getIsRunning()) {
        try {
            std::getline(std::cin, input);
            const auto parsedCommand {Console::CommandParser::parse(input)};
            commandRepository.execute(parsedCommand.getName(), parsedCommand.getParameters());
        } catch (const std::invalid_argument& exception) {
            std::cerr << exception.what() << '\n';
        }
    }

    return 0;
}