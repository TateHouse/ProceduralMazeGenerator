#include "MazeGenerator.hpp"

namespace Core {
MazeGenerator::MazeGenerator(const std::string_view mazeGenerationAlgorithmName) noexcept:
		mazeGenerationAlgorithmName {mazeGenerationAlgorithmName} {
}

MazeGenerator::~MazeGenerator() noexcept {
	delete seed;
}

const std::string& MazeGenerator::getMazeGenerationAlgorithmName() const noexcept {
	return mazeGenerationAlgorithmName;
}

const std::optional<unsigned long long> MazeGenerator::getSeed() const noexcept {
	return seed == nullptr ? std::nullopt : std::optional<unsigned long long>(*seed);
}

std::mt19937_64& MazeGenerator::getRandomEngine(const long long* seed) noexcept {
	delete this->seed;
	
	if (seed == nullptr) {
		std::random_device randomDevice {};
		this->seed = new unsigned long long(randomDevice());
	} else {
		this->seed = new unsigned long long(*seed);
	}
	
	randomEngine.seed(*this->seed);
}
}