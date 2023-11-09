#pragma once

#include "Command.hpp"

namespace Console {
class GridCommand final : public Command {
public:
    explicit GridCommand(Context& context) noexcept;
    GridCommand(const GridCommand& other) noexcept = default;
    GridCommand(GridCommand&& other) noexcept = default;
    ~GridCommand() noexcept override = default;

public:
    GridCommand& operator=(const GridCommand& other) noexcept = delete;
    GridCommand& operator=(GridCommand&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] virtual std::string getName() const noexcept override;
    [[nodiscard]] virtual std::string getDescription() const noexcept override;

private:
    static constexpr std::size_t defaultGridSize {10};
};
}