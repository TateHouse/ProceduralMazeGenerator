#pragma once

#include <memory>

#include "SquareGrid.hpp"

namespace Console {
/**
 * @brief A shared context for the console application.
 * @class Context
 */
class Context final {
public:
	/**
	 * @brief Instantiates a new context.
	 */
    Context() noexcept = default;
	
	/**
	 * @brief Instantiates a new context by copying the given context.
	 * @param other The context to copy.
	 */
    Context(const Context& other) noexcept = delete;
	
	/**
	 * @brief Instantiates a new context by moving the given context.
	 * @param other The context to move.
	 */
    Context(Context&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the context.
	 */
    ~Context() noexcept = default;

public:
	/**
	 * @brief Assigns the given context to this context using copy semantics.
	 * @param other The context to copy.
	 * @return A reference to this context.
	 */
    Context& operator=(const Context& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given context to this context using move semantics.
	 * @param other The context to move.
	 * @return A reference to this context.
	 */
    Context& operator=(Context&& other) noexcept = delete;

public:
	/**
	 * @brief Gets whether the application is running.
	 * @return True if the application is running; otherwise, false.
	 */
    [[nodiscard]] const bool getIsRunning() const noexcept;
	
	/**
	 * @brief Sets the application to not running.
	 */
    void setIsNotRunning() noexcept;
	
	/**
	 * @brief Instantiates a new grid with the given size.
	 * @param size The size of the grid.
	 */
    void setGrid(const std::size_t size);
	
	/**
	 * @brief Gets a const pointer to the const grid.
	 * @return A const pointer to the const grid.
	 */
    [[nodiscard]] const Core::Grid* const getGrid() const noexcept;
	
	/**
	 * @brief Gets a const pointer to the grid.
	 * @return A const pointer to the grid.
	 */
    [[nodiscard]] Core::Grid* const getGrid() noexcept;

private:
    bool isRunning {true};
    std::unique_ptr<Core::Grid> grid {nullptr};
};
}