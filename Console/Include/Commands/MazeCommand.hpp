#pragma once

#include <memory>
#include <vector>

#include "Command.hpp"
#include "MazeGenerator.hpp"

namespace Console {
class MazeCommand final : public Command {
public:
    explicit MazeCommand(Context& context) noexcept;
    MazeCommand(const MazeCommand& other) noexcept = default;
    MazeCommand(MazeCommand&& other) noexcept = default;
    ~MazeCommand() noexcept override = default;

public:
    MazeCommand& operator=(const MazeCommand& other) noexcept = delete;
    MazeCommand& operator=(MazeCommand&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] virtual std::string getName() const noexcept override;
    [[nodiscard]] virtual std::string getDescription() const noexcept override;

private:
    std::vector<std::unique_ptr<Core::MazeGenerator>> mazeGenerators {};
};
}