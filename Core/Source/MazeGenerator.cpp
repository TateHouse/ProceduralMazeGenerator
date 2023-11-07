#include "MazeGenerator.hpp"

namespace Core {
MazeGenerator::MazeGenerator(const std::string_view algorithmName) noexcept:
        algorithmName {algorithmName} {
}

const std::string& MazeGenerator::getAlgorithmName() const noexcept {
    return algorithmName;
}

const std::optional<unsigned long long> MazeGenerator::getSeed() const noexcept {
	return seedGenerator.getSeed();
}

const std::mt19937_64& MazeGenerator::getRandomEngine(const unsigned long long* seed) noexcept {
	return seedGenerator.getRandomEngine(seed);
}
}
