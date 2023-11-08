#pragma once

#include "CommandRepository.hpp"
#include "ParsedCommandInput.hpp"

namespace Console {
class CommandInterpreter final {
public:
    explicit CommandInterpreter(CommandRepository& commandRepository) noexcept;
    CommandInterpreter(const CommandInterpreter& other) noexcept = delete;
    CommandInterpreter(CommandInterpreter&& other) noexcept = delete;
    ~CommandInterpreter() noexcept = default;

public:
    CommandInterpreter& operator=(const CommandInterpreter& other) noexcept = delete;
    CommandInterpreter& operator=(CommandInterpreter&& other) noexcept = delete;

public:
    [[nodiscard]] ParsedCommandInput interpret(const std::string& input) const;

private:
    CommandRepository& commandRepository;
};
}