#pragma once

#include "ParsedCommandInput.hpp"

namespace Console {
class CommandParser final {
public:
    CommandParser() noexcept = delete;
    CommandParser(const CommandParser& other) noexcept = delete;
    CommandParser(CommandParser&& other) noexcept = delete;
    ~CommandParser() noexcept = delete;

public:
    CommandParser& operator=(const CommandParser& other) noexcept = delete;
    CommandParser& operator=(CommandParser&& other) noexcept = delete;

public:
    [[nodiscard]] static ParsedCommandInput parse(const std::string& input);
};
}