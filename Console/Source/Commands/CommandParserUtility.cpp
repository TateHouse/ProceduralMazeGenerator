#include "Commands/CommandParametersUtility.hpp"

#include <stdexcept>

namespace Console {
std::string CommandParametersUtility::getParameterValue(const std::unordered_map<std::string, std::string>& parameters,
                                                        const std::string& parameterName) {
    auto iterator {parameters.find(parameterName)};
    if (iterator == parameters.end()) {
        throw std::invalid_argument {"Parameter not found: " + parameterName};
    }

    if (iterator->second.empty()) {
        throw std::invalid_argument {"Parameter value is empty: " + parameterName};
    }

    return iterator->second;
}
}