#include "SeedGenerator.hpp"

namespace Core {
SeedGenerator::~SeedGenerator() noexcept {
	delete seed;
}

std::optional<unsigned long long> SeedGenerator::getSeed() const noexcept {
	return seed == nullptr ? std::nullopt : std::optional<unsigned long long>(*seed);
}

const std::mt19937_64& SeedGenerator::getRandomEngine(const unsigned long long* seed) noexcept {
	delete this->seed;
	
	if (seed == nullptr) {
		std::random_device randomDevice {};
		this->seed = new unsigned long long(randomDevice());
	} else {
		this->seed = new unsigned long long(*seed);
	}
	
	randomEngine.seed(*this->seed);
	return randomEngine;
}
}