#pragma once

#include "ParsedCommandInput.hpp"

namespace Console {
class CommandParser final {
public:
	/**
	 * @brief Instantiates a new command parser.
	 */
    CommandParser() noexcept = delete;
	
	/**
	 * @brief Instantiates a new command parser by copying the given command parser.
	 * @param other The command parser to copy.
	 */
    CommandParser(const CommandParser& other) noexcept = delete;
	
	/**
	 * @brief Instantiates a new command parser by moving the given command parser.
	 * @param other The command parser to move.
	 */
    CommandParser(CommandParser&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the command parser.
	 */
    ~CommandParser() noexcept = delete;

public:
	/**
	 * @brief Assigns the given command parser to this command parser using copy semantics.
	 * @param other The command parser to copy.
	 * @return A reference to this command parser.
	 */
    CommandParser& operator=(const CommandParser& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given command parser to this command parser using move semantics.
	 * @param other The command parser to move.
	 * @return A reference to this command parser.
	 */
    CommandParser& operator=(CommandParser&& other) noexcept = delete;

public:
	/**
	 * @brief Parses the given input into a parsed command input.
	 * @param input The input to parse.
	 * @return The parsed command input.
	 * @throws std::invalid_argument Thrown if no command was entered or if the command entered contains an unexpected
	 * token.
	 */
    [[nodiscard]] static ParsedCommandInput parse(const std::string& input);
};
}