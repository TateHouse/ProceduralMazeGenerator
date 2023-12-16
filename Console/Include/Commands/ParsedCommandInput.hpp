#pragma once

#include <string>
#include <unordered_map>

namespace Console {
/**
 * @brief A class for representing parsed command input.
 * @class ParsedCommandInput
 */
class ParsedCommandInput final {
public:
	/**
	 * @brief Instantiates a new parsed command input.
	 * @param name The name of the command.
	 * @param parameters The parameters for the command.
	 */
    ParsedCommandInput(const std::string& name,
                       const std::unordered_map<std::string, std::string>& parameters) noexcept;
	
	/**
	 * @brief Instantiates a new parsed command input by copying the given parsed command input.
	 * @param other The parsed command input to copy.
	 */
    ParsedCommandInput(const ParsedCommandInput& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new parsed command input by moving the given parsed command input.
	 * @param other The parsed command input to move.
	 */
    ParsedCommandInput(ParsedCommandInput&& other) noexcept = default;
	
	/**
	 * @brief Destroys the parsed command input.
	 */
    ~ParsedCommandInput() noexcept = default;

public:
	/**
	 * @brief Assigns the given parsed command input to this parsed command input using copy semantics.
	 * @param other The parsed command input to copy.
	 * @return A reference to this parsed command input.
	 */
    ParsedCommandInput& operator=(const ParsedCommandInput& other) noexcept = default;
	
	/**
	 * @brief Assigns the given parsed command input to this parsed command input using move semantics.
	 * @param other The parsed command input to move.
	 * @return A reference to this parsed command input.
	 */
    ParsedCommandInput& operator=(ParsedCommandInput&& other) noexcept = default;

public:
	/**
	 * @brief Gets the name of the parsed command.
	 * @return The name of the parsed command.
	 */
    [[nodiscard]] const std::string& getName() const noexcept;
	
	/**
	 * @brief Gets the parameters for the parsed command.
	 * @return The parameters for the parsed command.
	 */
    [[nodiscard]] const std::unordered_map<std::string, std::string>& getParameters() const noexcept;

private:
    std::string name;
    std::unordered_map<std::string, std::string> parameters;
};
}