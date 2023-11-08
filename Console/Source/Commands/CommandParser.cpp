#include "Commands/CommandParser.hpp"

#include <sstream>
#include <vector>

namespace Console {
CommandParser::CommandParser(CommandRepository& commandRepository) noexcept:
        commandRepository {commandRepository} {

};

ParsedCommandInput CommandParser::interpret(const std::string& input) const {
    std::istringstream stringStream {input};
    std::vector<std::string> tokens {std::istream_iterator<std::string> {stringStream},
                                     std::istream_iterator<std::string> {}};

    if (tokens.empty()) {
        throw std::invalid_argument {"No command entered"};
    }

    const auto commandName {tokens[0]};
    std::unordered_map<std::string, std::string> parameters {};

    for (std::size_t index {0}; index < tokens.size(); index = index + 2) {
        if (tokens[index][0] == '-') {
            const auto parameterValue {(index + 1) < tokens.size() ? tokens[index + 1] : ""};
            parameters[tokens[index]] = parameterValue;
        }
    }

    return {commandName, parameters};
}
}