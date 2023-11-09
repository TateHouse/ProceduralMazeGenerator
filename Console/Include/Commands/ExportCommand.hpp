#pragma once

#include <filesystem>

#include "Command.hpp"

namespace Console {
class ExportCommand final : public Command {
public:
    explicit ExportCommand(Context& context) noexcept;
    ExportCommand(const ExportCommand& other) noexcept = default;
    ExportCommand(ExportCommand&& other) noexcept = default;
    ~ExportCommand() noexcept override = default;

public:
    ExportCommand& operator=(const ExportCommand& other) noexcept = delete;
    ExportCommand& operator=(ExportCommand&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] virtual std::string getName() const noexcept override;
    [[nodiscard]] virtual std::string getDescription() const noexcept override;
};
}
