#pragma once

#include <optional>
#include <random>
#include <string>

#include "Grid.hpp"
#include "SeedGenerator.hpp"

namespace Core {
class MazeGenerator {
protected:
	explicit MazeGenerator(const std::string_view mazeGenerationAlgorithmName) noexcept;

public:
	virtual ~MazeGenerator() noexcept = default;

public:
	virtual void generate(Grid* const grid, const unsigned long long* seed) noexcept = 0;
	[[nodiscard]] const std::string& getMazeGenerationAlgorithmName() const noexcept;
	[[nodiscard]] const std::optional<unsigned long long> getSeed() const noexcept;

protected:
	const std::mt19937_64& getRandomEngine(const unsigned long long* seed) noexcept;

private:
	std::string mazeGenerationAlgorithmName;
	SeedGenerator seedGenerator {};
};
}