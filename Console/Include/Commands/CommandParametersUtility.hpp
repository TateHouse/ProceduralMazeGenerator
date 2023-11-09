#pragma once

#include <string>
#include <unordered_map>

namespace Console {
class CommandParametersUtility final {
public:
    CommandParametersUtility() = delete;
    CommandParametersUtility(const CommandParametersUtility& other) = delete;
    CommandParametersUtility(CommandParametersUtility&& other) = delete;
    ~CommandParametersUtility() = delete;

public:
    CommandParametersUtility& operator=(const CommandParametersUtility& other) = delete;
    CommandParametersUtility& operator=(CommandParametersUtility&& other) = delete;

public:
    static std::string getParameterValue(const std::unordered_map<std::string, std::string>& parameters,
                                         const std::string& parameterName);
};
}