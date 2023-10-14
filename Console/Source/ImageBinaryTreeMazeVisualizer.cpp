#include "ImageBinaryTreeMazeVisualizer.hpp"

namespace Console {
ImageBinaryTreeMazeVisualizer::ImageBinaryTreeMazeVisualizer(const Core::Grid* const grid,
                                                             const int cellSize,
                                                             const int borderSize,
                                                             const std::string_view imagePath,
                                                             const cv::Scalar& backgroundColor,
                                                             const cv::Scalar& gridColor) :
		grid {grid},
		cellSize {cellSize},
		borderSize {borderSize},
		imagePath {imagePath.data()},
		backgroundColor {backgroundColor},
		gridColor {gridColor} {
	if (cellSize < 1) {
		throw std::invalid_argument {"Cell size must be greater than 0."};
	}
	
	if (borderSize < 1) {
		throw std::invalid_argument {"Border size must be greater than 0."};
	}
}

void ImageBinaryTreeMazeVisualizer::visualize() noexcept {
	const auto [gridWidth, gridHeight] {grid->getSize()};
	
	const auto imageWidth {cellSize * gridWidth + (2 * borderSize)};
	const auto imageHeight {cellSize * gridHeight + (2 * borderSize)};
	
	auto image {cv::Mat {imageHeight, imageWidth, CV_8UC3, backgroundColor}};
	
	for (auto row {gridHeight - 1}; row >= 0; --row) {
		for (auto column {0}; column < gridWidth; ++column) {
			const auto position {std::pair<const int, const int> {column, row}};
			const auto* const cell {(*grid)[position]};
			
			auto topLeftY {imageHeight - (row + 1) * cellSize - borderSize};
			auto topLeftX {column * cellSize + borderSize};
			
			const auto* const eastNeighbor {cell->getEast()};
			const auto* const southNeighbor {cell->getSouth()};
			
			if (column != gridWidth - 1 && (eastNeighbor == nullptr || !cell->isLinked(eastNeighbor))) {
				const auto [topPoint, bottomPoint] {calculateVerticalPoints(row, topLeftX, topLeftY)};
				cv::line(image, topPoint, bottomPoint, gridColor);
			}
			
			if (row != 0 && (southNeighbor == nullptr || !cell->isLinked(southNeighbor))) {
				const auto [leftPoint, rightPoint] {calculateHorizontalPoints(topLeftX, topLeftY)};
				cv::line(image, leftPoint, rightPoint, gridColor);
			}
		}
	}
	
	drawOuterNorthWall(imageWidth, image);
	drawOuterWestWall(imageHeight, image);
	drawOuterSouthWall(imageWidth, imageHeight, image);
	drawOuterEastWall(imageWidth, imageHeight, image);
	
	cv::imwrite(imagePath, image);
}

std::pair<const cv::Point, const cv::Point> ImageBinaryTreeMazeVisualizer::calculateVerticalPoints(const int row,
                                                                                                   const int topLeftX,
                                                                                                   const int topLeftY) const noexcept {
	auto adjustedTopLeftY {topLeftY};
	if (row == 0) {
		adjustedTopLeftY -= 1;
	}
	
	const auto topPoint {cv::Point(topLeftX + cellSize, topLeftY)};
	const auto bottomPoint {cv::Point(topLeftX + cellSize, adjustedTopLeftY + cellSize)};
	
	return {topPoint, bottomPoint};
}

std::pair<const cv::Point, const cv::Point> ImageBinaryTreeMazeVisualizer::calculateHorizontalPoints(const int topLeftX,
                                                                                                     const int topLeftY) const noexcept {
	const auto leftPoint {cv::Point(topLeftX, topLeftY + cellSize)};
	const auto rightPoint {cv::Point(topLeftX + cellSize, topLeftY + cellSize)};
	
	return {leftPoint, rightPoint};
}

void ImageBinaryTreeMazeVisualizer::drawOuterNorthWall(int imageWidth, const cv::Mat& image) const noexcept {
	const auto leftPoint {cv::Point(borderSize, borderSize)};
	const auto rightPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};
	
	cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageBinaryTreeMazeVisualizer::drawOuterWestWall(int imageHeight, const cv::Mat& image) const noexcept {
	const auto topPoint {cv::Point(borderSize, borderSize)};
	const auto bottomPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};
	
	cv::line(image, topPoint, bottomPoint, gridColor);
}

void ImageBinaryTreeMazeVisualizer::drawOuterSouthWall(int imageWidth,
                                                       int imageHeight,
                                                       const cv::Mat& image) const noexcept {
	const auto leftPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};
	const auto rightPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};
	
	cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageBinaryTreeMazeVisualizer::drawOuterEastWall(int imageWidth,
                                                      int imageHeight,
                                                      const cv::Mat& image) const noexcept {
	const auto topPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};
	const auto bottomPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};
	
	cv::line(image, topPoint, bottomPoint, gridColor);
}
}