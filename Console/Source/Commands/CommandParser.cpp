#include "Commands/CommandParser.hpp"

#include <iostream>
#include <sstream>
#include <vector>

namespace Console {
ParsedCommandInput CommandParser::parse(const std::string& input) {
    std::istringstream stringStream {input};
    std::vector<std::string> tokens {std::istream_iterator<std::string> {stringStream},
                                     std::istream_iterator<std::string> {}};

    if (tokens.empty()) {
        throw std::invalid_argument {"No command entered"};
    }

    const auto commandName {tokens[0]};
    std::unordered_map<std::string, std::string> parameters {};

    for (std::size_t index {1}; index < tokens.size(); index = index + 2) {
        if (tokens[index][0] == '-') {
            std::string parameterValue {};

            if ((index + 1) < tokens.size() && (tokens[index + 1][0] != '-')) {
                parameterValue = tokens[index + 1];
            }

            parameters[tokens[index]] = parameterValue;
        } else {
            throw std::invalid_argument {"Unexpected token: " + tokens[index]};
        }
    }

    return {commandName, parameters};
}
}