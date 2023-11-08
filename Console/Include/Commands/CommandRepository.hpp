#pragma once

#include <string_view>

#include "../Context.hpp"

namespace Console {
class CommandRepository {
public:
    explicit CommandRepository(Context& context) noexcept;
    virtual ~CommandRepository() noexcept = default;

public:
    virtual void execute(const std::string_view command) = 0;

protected:
    Context& context;
};
}