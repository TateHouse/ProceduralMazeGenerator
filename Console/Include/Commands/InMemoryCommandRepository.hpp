#pragma once

#include <memory>
#include <unordered_map>

#include "Command.hpp"
#include "CommandRepository.hpp"

namespace Console {
class InMemoryCommandRepository : public CommandRepository {
public:
    InMemoryCommandRepository(Context& context) noexcept;
    InMemoryCommandRepository(const InMemoryCommandRepository& other) noexcept = delete;
    InMemoryCommandRepository(InMemoryCommandRepository&& other) noexcept = delete;
    ~InMemoryCommandRepository() noexcept override = default;

public:
    InMemoryCommandRepository& operator=(const InMemoryCommandRepository& other) noexcept = delete;
    InMemoryCommandRepository& operator=(InMemoryCommandRepository&& other) noexcept = delete;

public:
    virtual void execute(const std::string_view command) override;

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands {};
};
}