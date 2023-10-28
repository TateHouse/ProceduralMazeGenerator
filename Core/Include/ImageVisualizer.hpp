#pragma once

#include <opencv2/opencv.hpp>

#include <filesystem>

#include "Grid.hpp"
#include "GridVisualizer.hpp"
#include "ImageVisualizerBuilder.hpp"

namespace Core {
class ImageVisualizer final : public Core::GridVisualizer {
public:
    static ImageVisualizerBuilder create(const Core::Grid* const grid, const std::filesystem::path& imagePath);

private:
    ImageVisualizer(const Core::Grid* const grid,
                    const std::filesystem::path& imagePath,
                    const int cellSize,
                    const int borderSize,
                    const cv::Scalar& backgroundColor,
                    const cv::Scalar& gridColor);

public:
    void visualize() const noexcept override;

private:
    [[nodiscard]] std::pair<const cv::Point, const cv::Point> calculateVerticalPoints(const bool isFirstRow,
                                                                                      const int topLeftX,
                                                                                      const int topLeftY) const noexcept;
    [[nodiscard]] std::pair<const cv::Point, const cv::Point> calculateHorizontalPoints(const bool isLastColumn,
                                                                                        const int topLeftX,
                                                                                        const int topLeftY) const noexcept;

    void drawOuterNorthWall(const int imageWidth, cv::Mat& image) const noexcept;
    void drawOuterWestWall(const int imageHeight, cv::Mat& image) const noexcept;
    void drawOuterSouthWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept;
    void drawOuterEastWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept;

private:
    const Core::Grid* const grid;
    const std::filesystem::path& imagePath;
    const int cellSize {5};
    const int borderSize {0};
    const cv::Scalar backgroundColor {0.0f, 0.0f, 0.0f};
    const cv::Scalar gridColor {255.0f, 255.0f, 255.0f};

    friend class ImageVisualizerBuilder;
};
}