#pragma once

#include <string>
#include <unordered_map>

#include "../Context.hpp"

namespace Console {
/**
 * @brief The base class for all console commands.
 * @class Command
 */
class Command {
public:
	/**
	 * @brief Instantiates a new command.
	 * @param context The shared context for the console application.
	 */
    explicit Command(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new command by copying the given command.
	 * @param other The command to copy.
	 */
    Command(const Command& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new command by moving the given command.
	 * @param other The command to move.
	 */
    Command(Command&& other) noexcept = default;
	
	/**
	 * @brief Destroys the command.
	 */
	virtual ~Command() noexcept = default;

public:
	/**
	 * @brief Assigns the given command to this command using copy semantics.
	 * @param other The command to copy.
	 * @return A reference to this command.
	 */
    Command& operator=(const Command& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given command to this command using move semantics.
	 * @param other The command to move.
	 * @return A reference to this command.
	 */
    Command& operator=(Command&& other) noexcept = delete;

public:
	/**
	 * @brief Executes this command with the given parameters.
	 * @param parameters The parameters for this command.
	 */
    virtual void execute(const std::unordered_map<std::string, std::string>& parameters) = 0;
	
	/**
	 * @brief Gets the name of this command.
	 * @return The name of this command.
	 */
    [[nodiscard]] virtual std::string getName() const noexcept = 0;
	
	/**
	 * @brief Gets the description of this command.
	 * @return The description of this command.
	 */
    [[nodiscard]] virtual std::string getDescription() const noexcept = 0;

protected:
    Context& context;
};
}