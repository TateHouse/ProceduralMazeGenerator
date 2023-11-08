#include "Context.hpp"

namespace Console {
const bool Context::getIsRunning() const noexcept {
    return isRunning;
}

void Context::setIsNotRunning() noexcept {
    isRunning = false;
}

void Context::setGrid(const std::size_t size) {
    grid = std::make_unique<Core::SquareGrid>(size);
}

const Core::Grid* const Context::getGrid() const noexcept {
    return grid.get();
}

Core::Grid* const Context::getGrid() noexcept {
    return grid.get();
}
}