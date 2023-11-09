#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Command.hpp"

namespace Console {
class CommandFactory final {
public:
    explicit CommandFactory(Context& context) noexcept;
    CommandFactory(const CommandFactory& other) noexcept = delete;
    CommandFactory(CommandFactory&& other) noexcept = delete;
    ~CommandFactory() noexcept = default;

public:
    CommandFactory& operator=(const CommandFactory& other) noexcept = delete;
    CommandFactory& operator=(CommandFactory&& other) noexcept = delete;

public:
    [[nodiscard]] std::unique_ptr<Command> create(const std::string& name) const noexcept;

private:
    Context& context;
    std::unordered_map<std::string, std::function<std::unique_ptr<Command>(Context&)>> commands {};
};
}