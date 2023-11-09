#pragma once

#include <memory>
#include <optional>

#include "SquareGrid.hpp"

namespace Console {
class Context final {
public:
    Context() noexcept = default;
    Context(const Context& other) noexcept = delete;
    Context(Context&& other) noexcept = delete;
    ~Context() noexcept = default;

public:
    Context& operator=(const Context& other) noexcept = delete;
    Context& operator=(Context&& other) noexcept = delete;

public:
    [[nodiscard]] const bool getIsRunning() const noexcept;
    void setIsNotRunning() noexcept;
    void setGrid(const std::size_t size);
    [[nodiscard]] const Core::Grid* const getGrid() const noexcept;
    [[nodiscard]] Core::Grid* const getGrid() noexcept;

private:
    bool isRunning {true};
    std::unique_ptr<Core::Grid> grid {nullptr};
};
}