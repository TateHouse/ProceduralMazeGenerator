#include "ImageVisualizerBuilder.hpp"

#include <stdexcept>

#include "ImageVisualizer.hpp"

namespace Core {
ImageVisualizerBuilder::ImageVisualizerBuilder(Core::Grid* grid, std::filesystem::path& imagePath) :
        grid {grid}, imagePath {imagePath} {
    if (grid == nullptr) {
        throw std::invalid_argument {"The grid cannot be null."};
    }

    const auto directoryPath {imagePath.parent_path()};

    if (!std::filesystem::exists(directoryPath)) {
        try {
            std::filesystem::create_directory(directoryPath);
        } catch (const std::filesystem::filesystem_error& exception) {
            throw std::invalid_argument {"The directory path is invalid."};
        }
    }
}

ImageVisualizerBuilder& ImageVisualizerBuilder::setCellSize(const int cellSize) {
    if (cellSize <= 0) {
        throw std::invalid_argument {"The cell size must be greater than zero."};
    }

    this->cellSize = cellSize;
    return *this;
}

ImageVisualizerBuilder& ImageVisualizerBuilder::setBorderSize(const int borderSize) {
    if (borderSize < 0) {
        throw std::invalid_argument {"The border size cannot be negative."};
    }

    this->borderSize = borderSize;
    return *this;
}

ImageVisualizerBuilder& ImageVisualizerBuilder::setBackgroundColor(const cv::Scalar& backgroundColor) {
    this->backgroundColor = backgroundColor;
    return *this;
}

ImageVisualizerBuilder& ImageVisualizerBuilder::setGridColor(const cv::Scalar& gridColor) {
    this->gridColor = gridColor;
    return *this;
}

std::unique_ptr<ImageVisualizer> ImageVisualizerBuilder::build() {
    return std::unique_ptr<ImageVisualizer> {
            new ImageVisualizer {grid, imagePath, cellSize, borderSize, backgroundColor, gridColor}
    };
}
}