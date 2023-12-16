#pragma once

#include <string>
#include <unordered_map>

namespace Console {
/**
 * @brief A utility class for working with command parameters.
 * @class CommandParametersUtility
 */
class CommandParametersUtility final {
public:
	/**
	 * @brief Instantiates a new command parameters utility.
	 */
    CommandParametersUtility() = delete;
	
	/**
	 * @brief Instantiates a new command parameters utility by copying the given command parameters utility.
	 * @param other The command parameters utility to copy.
	 */
    CommandParametersUtility(const CommandParametersUtility& other) = delete;
	
	/**
	 * @brief Instantiates a new command parameters utility by moving the given command parameters utility.
	 * @param other The command parameters utility to move.
	 */
    CommandParametersUtility(CommandParametersUtility&& other) = delete;
	
	/**
	 * @brief Destroys the command parameters utility.
	 */
    ~CommandParametersUtility() = delete;

public:
	/**
	 * @brief Assigns the given command parameters utility to this command parameters utility using copy semantics.
	 * @param other The command parameters utility to copy.
	 * @return A reference to this command parameters utility.
	 */
    CommandParametersUtility& operator=(const CommandParametersUtility& other) = delete;
	
	/**
	 * @brief Assigns the given command parameters utility to this command parameters utility using move semantics.
	 * @param other The command parameters utility to move.
	 * @return A reference to this command parameters utility.
	 */
    CommandParametersUtility& operator=(CommandParametersUtility&& other) = delete;

public:
	/**
	 * @brief Gets the value of the parameter with the given name.
	 * @param parameters The parameters to search through.
	 * @param parameterName The name of the parameter to get the value of.
	 * @return The value of the parameter with the given name.
	 * @throws std::invalid_argument Thrown if the parameter with the given name does not exist or if the value of the
	 * parameter with the given name is empty.
	 */
    static std::string getParameterValue(const std::unordered_map<std::string, std::string>& parameters,
                                         const std::string& parameterName);
};
}