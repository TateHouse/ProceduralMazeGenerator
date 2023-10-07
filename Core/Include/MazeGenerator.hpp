#pragma once

#include <optional>
#include <random>
#include <string>

#include "Grid.hpp"

namespace Core {
class MazeGenerator {
protected:
	MazeGenerator(const std::string_view mazeGenerationAlgorithmName) noexcept;

public:
	virtual ~MazeGenerator() noexcept;

public:
	virtual void generate(Grid* const grid, const long long* seed) noexcept = 0;
	[[nodiscard]] const std::string& getMazeGenerationAlgorithmName() const noexcept;
	[[nodiscard]] const std::optional<unsigned long long> getSeed() const noexcept;

protected:
	std::mt19937_64& getRandomEngine(const long long* seed) noexcept;

private:
	std::string mazeGenerationAlgorithmName;
	unsigned long long* seed {nullptr};
	std::mt19937_64 randomEngine {};
};
}