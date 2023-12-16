#pragma once

#include <map>

#include "Commands/Command.hpp"

namespace Console {
/**
 * @brief A console command for displaying help information.
 * @class HelpCommand
 */
class HelpCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new help command.
	 * @param context The shared context for the console application.
	 */
    explicit HelpCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new help command by copying the given help command.
	 * @param other The help command to copy.
	 */
    HelpCommand(const HelpCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new help command by moving the given help command.
	 * @param other The help command to move.
	 */
    HelpCommand(HelpCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the help command.
	 */
    ~HelpCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given help command to this help command using copy semantics.
	 * @param other The help command to copy.
	 * @return A reference to this help command.
	 */
    HelpCommand& operator=(const HelpCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given help command to this help command using move semantics.
	 * @param other The help command to move.
	 * @return A reference to this help command.
	 */
    HelpCommand& operator=(HelpCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
    [[nodiscard]] std::string getName() const noexcept override;
    [[nodiscard]] std::string getDescription() const noexcept override;

public:
	/**
	 * @brief Sets the commands to display help information for.
	 * @param commands The commands to display help information for.
	 */
    void setCommands(const std::map<std::string, std::string>& commands) noexcept;

private:
    std::map<std::string, std::string> commands {};
};
}