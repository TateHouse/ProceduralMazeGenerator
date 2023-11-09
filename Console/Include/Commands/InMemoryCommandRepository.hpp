#pragma once

#include <memory>
#include <unordered_map>

#include "Commands/Command.hpp"
#include "Commands/CommandRepository.hpp"

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
    virtual void add(std::unique_ptr<Command> command) override;
    virtual void execute(const std::string_view command,
                         const std::unordered_map<std::string, std::string>& parameters) override;

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands {};
};
}