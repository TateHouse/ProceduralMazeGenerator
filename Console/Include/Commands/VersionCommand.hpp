#pragma once

#include "Command.hpp"

namespace Console {
/**
 * @brief A console command for displaying the project version.
 * @class VersionCommand
 */
class VersionCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new version command.
	 * @param context The shared context for the console application.
	 */
	explicit VersionCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new version command by copying the given version command.
	 * @param other The version command to copy.
	 */
	VersionCommand(const VersionCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new version command by moving the given version command.
	 * @param other The version command to move.
	 */
	VersionCommand(VersionCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the version command.
	 */
	~VersionCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given version command to this version command using copy semantics.
	 * @param other The version command to copy.
	 * @return A reference to this version command.
	 */
	VersionCommand& operator=(const VersionCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given version command to this version command using move semantics.
	 * @param other The version command to move.
	 * @return A reference to this version command.
	 */
	VersionCommand& operator=(VersionCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;
};
}