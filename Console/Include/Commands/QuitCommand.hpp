#pragma once

#include "Command.hpp"

namespace Console {
/**
 * @brief A console command for quitting the console application.
 * @class QuitCommand
 */
class QuitCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new quit command.
	 * @param context The shared context for the console application.
	 */
	explicit QuitCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new quit command by copying the given quit command.
	 * @param other The quit command to copy.
	 */
	QuitCommand(const QuitCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new quit command by moving the given quit command.
	 * @param other The quit command to move.
	 */
	QuitCommand(QuitCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the quit command.
	 */
	~QuitCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given quit command to this quit command using copy semantics.
	 * @param other The quit command to copy.
	 * @return A reference to this quit command.
	 */
	QuitCommand& operator=(const QuitCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given quit command to this quit command using move semantics.
	 * @param other The quit command to move.
	 * @return A reference to this quit command.
	 */
	QuitCommand& operator=(QuitCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;
};
}