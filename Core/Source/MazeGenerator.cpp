#include "MazeGenerator.hpp"

namespace Core {
MazeGenerator::MazeGenerator(const std::string_view mazeGenerationAlgorithmName) noexcept:
		mazeGenerationAlgorithmName {mazeGenerationAlgorithmName} {
}

const std::string& MazeGenerator::getMazeGenerationAlgorithmName() const noexcept {
	return mazeGenerationAlgorithmName;
}

const std::optional<unsigned long long> MazeGenerator::getSeed() const noexcept {
	return seedGenerator.getSeed();
}

const std::mt19937_64& MazeGenerator::getRandomEngine(const unsigned long long* seed) noexcept {
	return seedGenerator.getRandomEngine(seed);
}
}
