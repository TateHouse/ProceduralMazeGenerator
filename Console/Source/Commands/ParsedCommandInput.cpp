#include "Commands/ParsedCommandInput.hpp"

namespace Console {
ParsedCommandInput::ParsedCommandInput(const std::string& name,
                                       const std::unordered_map<std::string, std::string>& parameters) noexcept
        : name {name}, parameters {parameters} {

}

const std::string& ParsedCommandInput::getName() const noexcept {
    return name;
}

const std::unordered_map<std::string, std::string>& ParsedCommandInput::getParameters() const noexcept {
    return parameters;
}
}