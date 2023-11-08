#pragma once

#include <string>
#include <unordered_map>

#include "../Context.hpp"

namespace Console {
class Command {
public:
    explicit Command(Context& context) noexcept;
    Command(const Command& other) noexcept = default;
    Command(Command&& other) noexcept = default;
    virtual ~Command() noexcept = default;

public:
    Command& operator=(const Command& other) noexcept = delete;
    Command& operator=(Command&& other) noexcept = delete;

public:
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) noexcept = 0;
    virtual std::string getName() const noexcept = 0;
    virtual std::string getHelp() const noexcept = 0;

protected:
    Context& context;
};
}