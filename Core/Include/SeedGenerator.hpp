#pragma once

#include <optional>
#include <random>

namespace Core {
class SeedGenerator {
public:
	SeedGenerator() noexcept = default;
	SeedGenerator(const SeedGenerator& seedGenerator) noexcept = delete;
	SeedGenerator(SeedGenerator&& seedGenerator) noexcept = delete;
    ~SeedGenerator() noexcept = default;

public:
	SeedGenerator& operator=(const SeedGenerator& seedGenerator) noexcept = delete;
	SeedGenerator& operator=(SeedGenerator&& seedGenerator) noexcept = delete;

public:
	[[nodiscard]] std::optional<unsigned long long> getSeed() const noexcept;
    [[nodiscard]] const std::mt19937_64& getRandomEngine(const std::optional<unsigned long long>& seed) noexcept;

private:
    std::optional<unsigned long long> seed {};
	std::mt19937_64 randomEngine {};
};
}