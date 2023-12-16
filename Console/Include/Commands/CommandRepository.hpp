#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include "Commands/Command.hpp"

namespace Console {
/**
 * @brief The base class for all command repositories.
 * @class CommandRepository
 */
class CommandRepository {
public:
	/**
	 * @brief Instantiates a new command repository.
	 * @param context The shared context for the console application.
	 */
	explicit CommandRepository(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new command repository by copying the given command repository.
	 * @param other The command repository to copy.
	 */
	CommandRepository(const CommandRepository& other) noexcept = delete;
	
	/**
	 * @brief Instantiates a new command repository by moving the given command repository.
	 * @param other The command repository to move.
	 */
	CommandRepository(CommandRepository&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the command repository.
	 */
	virtual ~CommandRepository() noexcept = default;

public:
	/**
	 * @brief Assigns the given command repository to this command repository using copy semantics.
	 * @param other The command repository to copy.
	 * @return A reference to this command repository.
	 */
	CommandRepository& operator=(const CommandRepository& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given command repository to this command repository using move semantics.
	 * @param other The command repository to move.
	 * @return A reference to this command repository.
	 */
	CommandRepository& operator=(CommandRepository&& other) noexcept = delete;

public:
	/**
	 * @brief Adds the given command to this command repository.
	 * @param command The command to add.
	 */
	virtual void add(std::unique_ptr<Command> command) = 0;
	
	/**
	 * @brief Executes the command with the given name and parameters.
	 * @param command The name of the command to execute.
	 * @param parameters The parameters for the command.
	 */
	virtual void execute(const std::string_view command,
	                     const std::unordered_map<std::string, std::string>& parameters) = 0;

protected:
	Context& context;
};
}