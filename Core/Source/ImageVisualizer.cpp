#include "ImageVisualizer.hpp"

#include <stdexcept>

namespace Core {
ImageVisualizerBuilder ImageVisualizer::create(Core::Grid* grid, std::filesystem::path& imagePath) {
    return ImageVisualizerBuilder {grid, imagePath};
}

ImageVisualizer::ImageVisualizer(Core::Grid* grid,
                                 std::filesystem::path& imagePath,
                                 const int cellSize,
                                 const int borderSize,
                                 const cv::Scalar& backgroundColor,
                                 const cv::Scalar& gridColor) : grid {grid},
                                                                imagePath {imagePath},
                                                                cellSize {cellSize},
                                                                borderSize {borderSize},
                                                                backgroundColor {backgroundColor},
                                                                gridColor {gridColor} {

}

void ImageVisualizer::visualize() const noexcept {
    const auto [gridWidth, gridHeight] {grid->getSize()};
    const auto imageWidth {cellSize * gridWidth + (2 * borderSize)};
    const auto imageHeight {cellSize * gridHeight + (2 * borderSize)};
    auto image {cv::Mat {imageHeight, imageWidth, CV_8UC3, backgroundColor}};

    for (auto y {gridHeight - 1}; y >= 0; --y) {
        for (auto x {0}; x < gridWidth; ++x) {
            const auto position {std::pair<const int, const int> {x, y}};
            const auto* const cell {(*grid)[position]};

            auto topLeftX {x * cellSize + borderSize};
            auto topLeftY {imageHeight - (y + 1) * cellSize - borderSize};

            const auto* const eastNeighbor {cell->getEast()};
            if (x != gridWidth - 1 && (eastNeighbor == nullptr || !cell->isLinked(eastNeighbor))) {
                const bool isFirstRow {y == 0};
                const auto [topPoint, bottomPoint] {calculateVerticalPoints(isFirstRow, topLeftX, topLeftY)};
                cv::line(image, topPoint, bottomPoint, gridColor);
            }

            const auto* const southNeighbor {cell->getSouth()};
            if (y != 0 && (southNeighbor == nullptr || !cell->isLinked(southNeighbor))) {
                const bool isLastColumn {x == gridWidth - 1};
                const auto [leftPoint, rightPoint] {calculateHorizontalPoints(isLastColumn, topLeftX, topLeftY)};
                cv::line(image, leftPoint, rightPoint, gridColor);
            }
        }
    }

    drawOuterNorthWall(imageWidth, image);
    drawOuterWestWall(imageHeight, image);
    drawOuterSouthWall(imageWidth, imageHeight, image);
    drawOuterEastWall(imageWidth, imageHeight, image);

    cv::imwrite(imagePath.string(), image);
}

std::pair<const cv::Point, const cv::Point> ImageVisualizer::calculateVerticalPoints(const bool isFirstRow,
                                                                                     const int topLeftX,
                                                                                     const int topLeftY) const noexcept {
    auto adjustedTopLeftY {topLeftY};
    if (isFirstRow) {
        adjustedTopLeftY = adjustedTopLeftY - 1;
    }

    const auto topPoint {cv::Point(topLeftX + cellSize, topLeftY)};
    const auto bottomPoint {cv::Point(topLeftX + cellSize, adjustedTopLeftY + cellSize)};

    return {topPoint, bottomPoint};
}

std::pair<const cv::Point, const cv::Point> ImageVisualizer::calculateHorizontalPoints(const bool isLastColumn,
                                                                                       const int topLeftX,
                                                                                       const int topLeftY) const noexcept {
    auto adjustedTopLeftX {topLeftX};
    if (isLastColumn) {
        adjustedTopLeftX = adjustedTopLeftX - 1;
    }

    const auto leftPoint {cv::Point(topLeftX, topLeftY + cellSize)};
    const auto rightPoint {cv::Point(adjustedTopLeftX + cellSize, topLeftY + cellSize)};

    return {leftPoint, rightPoint};
}

void ImageVisualizer::drawOuterNorthWall(const int imageWidth, cv::Mat& image) const noexcept {
    const auto leftPoint {cv::Point(borderSize, borderSize)};
    const auto rightPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};

    cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageVisualizer::drawOuterWestWall(const int imageHeight, cv::Mat& image) const noexcept {
    const auto topPoint {cv::Point(borderSize, borderSize)};
    const auto bottomPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};

    cv::line(image, topPoint, bottomPoint, gridColor);
}

void ImageVisualizer::drawOuterSouthWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept {
    const auto leftPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};
    const auto rightPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};

    cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageVisualizer::drawOuterEastWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept {
    const auto topPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};
    const auto bottomPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};

    cv::line(image, topPoint, bottomPoint, gridColor);
}
}