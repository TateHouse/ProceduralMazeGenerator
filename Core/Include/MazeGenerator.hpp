#pragma once

#include <optional>
#include <random>
#include <string>

#include "Grid.hpp"
#include "SeedGenerator.hpp"

namespace Core {
class MazeGenerator {
protected:
    explicit MazeGenerator(const std::string_view algorithmName) noexcept;

public:
    virtual ~MazeGenerator() noexcept = default;

public:
    virtual void generate(Grid* const grid, const std::optional<unsigned long long>& seed) noexcept = 0;
    [[nodiscard]] const std::string& getAlgorithmName() const noexcept;
    [[nodiscard]] const std::optional<unsigned long long> getSeed() const noexcept;

protected:
    const std::mt19937_64& getRandomEngine(const std::optional<unsigned long long>& seed) noexcept;

private:
    std::string algorithmName;
    SeedGenerator seedGenerator {};
};
}