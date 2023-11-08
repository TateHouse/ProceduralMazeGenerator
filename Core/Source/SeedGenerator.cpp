#include "SeedGenerator.hpp"

namespace Core {
std::optional<unsigned long long> SeedGenerator::getSeed() const noexcept {
    return seed.has_value() ? std::optional<unsigned long long>(seed.value()) : std::nullopt;
}

const std::mt19937_64& SeedGenerator::getRandomEngine(const std::optional<unsigned long long>& seed) noexcept {
    if (seed.has_value()) {
        this->seed = seed.value();
    } else {
        std::random_device randomDevice {};
        this->seed = randomDevice();
    }

    randomEngine.seed(this->seed.value());
    return randomEngine;
}
}