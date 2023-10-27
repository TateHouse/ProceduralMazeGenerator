#pragma once

#include <string>

#include "MazeGenerator.hpp"

namespace Renderer {
const std::string getMazeGenerationAlgorithmName(const Core::MazeGenerator* const mazeGenerator) {
    if (mazeGenerator == nullptr) {
        return "None";
    }

    return mazeGenerator->getMazeGenerationAlgorithmName();
}
}