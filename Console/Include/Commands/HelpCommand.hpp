#pragma once

#include <map>

#include "Commands/Command.hpp"

namespace Console {
class HelpCommand final : public Command {
public:
    explicit HelpCommand(Context& context) noexcept;
    HelpCommand(const HelpCommand& other) noexcept = default;
    HelpCommand(HelpCommand&& other) noexcept = default;
    ~HelpCommand() noexcept override = default;

public:
    HelpCommand& operator=(const HelpCommand& other) noexcept = delete;
    HelpCommand& operator=(HelpCommand&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] virtual std::string getName() const noexcept override;
    [[nodiscard]] virtual std::string getDescription() const noexcept override;

public:
    void setCommands(const std::map<std::string, std::string>& commands) noexcept;

private:
    std::map<std::string, std::string> commands {};
};
}