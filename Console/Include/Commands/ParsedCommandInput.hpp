#pragma once

#include <string>
#include <unordered_map>

namespace Console {
class ParsedCommandInput final {
public:
    ParsedCommandInput(const std::string& name,
                       const std::unordered_map<std::string, std::string>& parameters) noexcept;
    ParsedCommandInput(const ParsedCommandInput& other) noexcept = default;
    ParsedCommandInput(ParsedCommandInput&& other) noexcept = default;
    ~ParsedCommandInput() noexcept = default;

public:
    ParsedCommandInput& operator=(const ParsedCommandInput& other) noexcept = default;
    ParsedCommandInput& operator=(ParsedCommandInput&& other) noexcept = default;

public:
    [[nodiscard]] const std::string& getName() const noexcept;
    [[nodiscard]] const std::unordered_map<std::string, std::string>& getParameters() const noexcept;

private:
    std::string name;
    std::unordered_map<std::string, std::string> parameters;
};
}