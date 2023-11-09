#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include "Commands/Command.hpp"

namespace Console {
class CommandRepository {
public:
    explicit CommandRepository(Context& context) noexcept;
    virtual ~CommandRepository() noexcept = default;

public:
    virtual void add(std::unique_ptr<Command> command) = 0;
    virtual void execute(const std::string_view command,
                         const std::unordered_map<std::string, std::string>& parameters) = 0;

protected:
    Context& context;
};
}