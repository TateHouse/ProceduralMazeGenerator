#pragma once

#include <string_view>
#include <unordered_map>

#include "../Context.hpp"

namespace Console {
class CommandRepository {
public:
    explicit CommandRepository(Context& context) noexcept;
    virtual ~CommandRepository() noexcept = default;

public:
    virtual void execute(const std::string_view command,
                         const std::unordered_map<std::string, std::string>& parameters) = 0;

protected:
    Context& context;
};
}