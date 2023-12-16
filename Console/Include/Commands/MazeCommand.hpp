#pragma once

#include <memory>
#include <vector>

#include "Command.hpp"
#include "MazeGenerator.hpp"

namespace Console {
/**
 * @brief A console command for modifying a grid to generate a maze.
 * @class MazeCommand
 */
class MazeCommand final : public Command {
public:
	/**
	 * @brief Instantiates a new maze command.
	 * @param context The shared context for the console application.
	 */
	explicit MazeCommand(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new maze command by copying the given maze command.
	 * @param other The maze command to copy.
	 */
	MazeCommand(const MazeCommand& other) noexcept = default;
	
	/**
	 * @brief Instantiates a new maze command by moving the given maze command.
	 * @param other The maze command to move.
	 */
	MazeCommand(MazeCommand&& other) noexcept = default;
	
	/**
	 * @brief Destroys the maze command.
	 */
	~MazeCommand() noexcept override = default;

public:
	/**
	 * @brief Assigns the given maze command to this maze command using copy semantics.
	 * @param other The maze command to copy.
	 * @return A reference to this maze command.
	 */
	MazeCommand& operator=(const MazeCommand& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given maze command to this maze command using move semantics.
	 * @param other The maze command to move.
	 * @return A reference to this maze command.
	 */
	MazeCommand& operator=(MazeCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;

private:
	std::vector<std::unique_ptr<Core::MazeGenerator>> mazeGenerators {};
};
}