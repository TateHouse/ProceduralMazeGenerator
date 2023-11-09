#pragma once

#include <gmock/gmock.h>

#include "Commands/Command.hpp"

namespace Console::Test {
class MockCommand final : public Command {
public:
    explicit MockCommand(Context& context) noexcept;
    MockCommand(const MockCommand&) = delete;
    MockCommand(MockCommand&&) noexcept = delete;
    virtual ~MockCommand() noexcept override = default;

public:
    MockCommand& operator=(const MockCommand&) = delete;
    MockCommand& operator=(MockCommand&&) noexcept = delete;

public:
    MOCK_METHOD(void, execute, ((const std::unordered_map<std::string, std::string>& parameters)), (override));
    MOCK_METHOD(std::string, getName, (), (const, noexcept, override));
    MOCK_METHOD(std::string, getDescription, (), (const, noexcept, override));
};
}