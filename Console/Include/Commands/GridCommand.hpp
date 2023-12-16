#pragma once

#include "Command.hpp"

namespace Console {
/**
 * @brief A console command for generating a grid.
 * @class GridCommand
 */
class GridCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new grid command.
	 * @param context The shared context for the console application.
	 */
	explicit GridCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new grid command by copying the given grid command.
	 * @param other The grid command to copy.
	 */
	GridCommand(const GridCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new grid command by moving the given grid command.
	 * @param other The grid command to move.
	 */
	GridCommand(GridCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the grid command.
	 */
	~GridCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given grid command to this grid command using copy semantics.
	 * @param other The grid command to copy.
	 * @return A reference to this grid command.
	 */
	GridCommand& operator=(const GridCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given grid command to this grid command using move semantics.
	 * @param other The grid command to move.
	 * @return A reference to this grid command.
	 */
	GridCommand& operator=(GridCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;

private:
	static constexpr std::size_t defaultGridSize {10};
};
}