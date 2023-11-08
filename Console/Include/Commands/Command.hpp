#pragma once

#include <string>

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
    virtual void execute() noexcept = 0;
    virtual std::string getName() const noexcept = 0;
    virtual std::string getHelp() const noexcept = 0;

protected:
    Context& context;
};
}