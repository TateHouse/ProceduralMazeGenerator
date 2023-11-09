#pragma once

#include "Command.hpp"

namespace Console {
class QuitCommand final : public Command {
public:
    explicit QuitCommand(Context& context) noexcept;
    QuitCommand(const QuitCommand& other) noexcept = default;
    QuitCommand(QuitCommand&& other) noexcept = default;
    ~QuitCommand() noexcept override = default;

public:
    QuitCommand& operator=(const QuitCommand& other) noexcept = delete;
    QuitCommand& operator=(QuitCommand&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] virtual std::string getName() const noexcept override;
    [[nodiscard]] virtual std::string getDescription() const noexcept override;
};
}