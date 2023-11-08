#pragma once

#include "CommandRepository.hpp"
#include "ParsedCommandInput.hpp"

namespace Console {
class CommandParser final {
public:
    explicit CommandParser(CommandRepository& commandRepository) noexcept;
    CommandParser(const CommandParser& other) noexcept = delete;
    CommandParser(CommandParser&& other) noexcept = delete;
    ~CommandParser() noexcept = default;

public:
    CommandParser& operator=(const CommandParser& other) noexcept = delete;
    CommandParser& operator=(CommandParser&& other) noexcept = delete;

public:
    [[nodiscard]] ParsedCommandInput interpret(const std::string& input) const;

private:
    CommandRepository& commandRepository;
};
}