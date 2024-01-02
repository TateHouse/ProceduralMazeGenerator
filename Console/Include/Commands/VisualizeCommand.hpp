#pragma once

#include "Command.hpp"

namespace Console {
/**
 * @brief A console command for visualizing a grid or maze in the console using ASCII.
 * @class VisualizeCommand
 */
class VisualizeCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new visualize command.
	 * @param context The shared context for the console application.
	 */
	explicit VisualizeCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new visualize command by copying the given visualize command.
	 * @param other The visualize command to copy.
	 */
	VisualizeCommand(const VisualizeCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new visualize command by moving the given visualize command.
	 * @param other The visualize command to move.
	 */
	VisualizeCommand(VisualizeCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the visualize command.
	 */
	~VisualizeCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given visualize command to this visualize command using copy semantics.
	 * @param other The visualize command to copy.
	 * @return A reference to this visualize command.
	 */
	VisualizeCommand& operator=(const VisualizeCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given visualize command to this visualize command using move semantics.
	 * @param other The visualize command to move.
	 * @return A reference to this visualize command.
	 */
	VisualizeCommand& operator=(VisualizeCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;
};
}