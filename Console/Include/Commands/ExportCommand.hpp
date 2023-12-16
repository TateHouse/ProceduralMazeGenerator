#pragma once

#include <filesystem>

#include "Command.hpp"

namespace Console {
/**
 * @brief A console command for exporting a grid to a PNG image.
 * @class ExportCommand
 */
class ExportCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new export command.
	 * @param context The shared context for the console application.
	 */
	explicit ExportCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new export command by copying the given export command.
	 * @param other The export command to copy.
	 */
	ExportCommand(const ExportCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new export command by moving the given export command.
	 * @param other The export command to move.
	 */
	ExportCommand(ExportCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the export command.
	 */
	~ExportCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given export command to this export command using copy semantics.
	 * @param other The export command to copy.
	 * @return A reference to this export command.
	 */
	ExportCommand& operator=(const ExportCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given export command to this export command using move semantics.
	 * @param other The export command to move.
	 * @return A reference to this export command.
	 */
	ExportCommand& operator=(ExportCommand&& other) noexcept = delete;

public:
	/**
	 * @brief Executes the export command with the given parameters.
	 * @param parameters The parameters to execute the export command with.
	 * @throws std::invalid_argument Thrown if the grid has not been generated.
	 */
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;
};
}
