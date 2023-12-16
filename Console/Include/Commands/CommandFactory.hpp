#pragma once

#include <functional>
#include <memory>
#include <string>

#include "Command.hpp"

namespace Console {
/**
 * @brief A factory for creating commands.
 * @class CommandFactory
 */
class CommandFactory final {
public:
	/**
	 * @brief Instantiates a new command factory.
	 * @param context The shared context for the console application.
	 */
    explicit CommandFactory(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new command factory by copying the given command factory.
	 * @param other The command factory to copy.
	 */
    CommandFactory(const CommandFactory& other) noexcept = delete;
	
	/**
	 * @brief Instantiates a new command factory by moving the given command factory.
	 * @param other The command factory to move.
	 */
    CommandFactory(CommandFactory&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the command factory.
	 */
    ~CommandFactory() noexcept = default;

public:
	/**
	 * @brief Assigns the given command factory to this command factory using copy semantics.
	 * @param other The command factory to copy.
	 * @return A reference to this command factory.
	 */
    CommandFactory& operator=(const CommandFactory& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given command factory to this command factory using move semantics.
	 * @param other The command factory to move.
	 * @return A reference to this command factory.
	 */
    CommandFactory& operator=(CommandFactory&& other) noexcept = delete;

public:
	/**
	 * @brief Instantiates a new command with the given name.
	 * @param name The name of the command to create.
	 * @return The command with the given name. If no command with the given name exists, then nullptr is returned.
	 */
    [[nodiscard]] std::unique_ptr<Command> create(const std::string& name) const noexcept;

private:
    Context& context;
    std::unordered_map<std::string, std::function<std::unique_ptr<Command>(Context&)>> commands {};
};
}