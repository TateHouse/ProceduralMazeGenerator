#pragma once

#include <memory>
#include <unordered_map>

#include "Commands/Command.hpp"
#include "Commands/CommandRepository.hpp"

namespace Console {
/**
 * @brief A command repository that stores console commands in memory.
 * @class InMemoryCommandRepository
 */
class InMemoryCommandRepository : public CommandRepository {
public:
	/**
	 * @brief Instantiates a new in-memory command repository.
	 * @param context The shared context for the console application.
	 */
	explicit InMemoryCommandRepository(Context& context) noexcept;
	
	/**
	 * @brief Instantiates a new in-memory command repository by copying the given in-memory command repository.
	 * @param other The in-memory command repository to copy.
	 */
	InMemoryCommandRepository(const InMemoryCommandRepository& other) noexcept = delete;
	
	/**
	 * @brief Instantiates a new in-memory command repository by moving the given in-memory command repository.
	 * @param other The in-memory command repository to move.
	 */
	InMemoryCommandRepository(InMemoryCommandRepository&& other) noexcept = delete;
	
	/**
	 * @brief Destroys the in-memory command repository.
	 */
	~InMemoryCommandRepository() noexcept override = default;

public:
	/**
	 * @brief Assigns the given in-memory command repository to this in-memory command repository using copy semantics.
	 * @param other The in-memory command repository to copy.
	 * @return A reference to this in-memory command repository.
	 */
	InMemoryCommandRepository& operator=(const InMemoryCommandRepository& other) noexcept = delete;
	
	/**
	 * @brief Assigns the given in-memory command repository to this in-memory command repository using move semantics.
	 * @param other The in-memory command repository to move.
	 * @return A reference to this in-memory command repository.
	 */
	InMemoryCommandRepository& operator=(InMemoryCommandRepository&& other) noexcept = delete;

public:
	void add(std::unique_ptr<Command> command) override;
	void execute(const std::string_view command,
	             const std::unordered_map<std::string, std::string>& parameters) override;

private:
	std::unordered_map<std::string, std::unique_ptr<Command>> commands {};
};
}