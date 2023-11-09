#pragma once

#include <opencv2/core.hpp>

#include <filesystem>
#include <memory>

#include "Grid.hpp"

namespace Core {
class ImageVisualizer;

class ImageVisualizerBuilder final {
public:
    ImageVisualizerBuilder(const Core::Grid* const grid, const std::filesystem::path& imagePath);
    ImageVisualizerBuilder(const ImageVisualizerBuilder&) = delete;
    ImageVisualizerBuilder(ImageVisualizerBuilder&&) = delete;
    ~ImageVisualizerBuilder() noexcept = default;

public:
    ImageVisualizerBuilder& operator=(const ImageVisualizerBuilder&) = delete;
    ImageVisualizerBuilder& operator=(ImageVisualizerBuilder&&) = delete;

public:
    ImageVisualizerBuilder& setCellSize(const int cellSize);
    ImageVisualizerBuilder& setBorderSize(const int borderSize);
    ImageVisualizerBuilder& setBackgroundColor(const cv::Scalar& backgroundColor);
    ImageVisualizerBuilder& setGridColor(const cv::Scalar& gridColor);

    std::unique_ptr<ImageVisualizer> build();

private:
    const Core::Grid* const grid;
    const std::filesystem::path& imagePath;
    int cellSize {5};
    int borderSize {0};
    cv::Scalar backgroundColor {255.0f, 255.0f, 255.0f};
    cv::Scalar gridColor {0.0f, 0.0f, 0.0f};
};
}