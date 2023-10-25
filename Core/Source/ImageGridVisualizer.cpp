#include "ImageGridVisualizer.hpp"

namespace Core {
ImageGridVisualizer::ImageGridVisualizer(const Core::Grid* const grid, const int cellSize, const int borderSize,
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

void ImageGridVisualizer::visualize() noexcept {
	const auto [gridWidth, gridHeight] {grid->getSize()};
	
	const auto imageWidth {static_cast<int>(cellSize * gridWidth + (2 * borderSize))};
	const auto imageHeight {static_cast<int>(cellSize * gridHeight + (2 * borderSize))};
	
	auto image {cv::Mat {imageHeight, imageWidth, CV_8UC3, backgroundColor}};
	
	for (std::size_t column {1}; column < gridWidth; ++column) {
		const auto [topPoint, bottomPoint] {calculateVerticalPoints(column, imageHeight)};
		cv::line(image, topPoint, bottomPoint, gridColor);
	}
	
	for (std::size_t row {1}; row < gridHeight; ++row) {
		const auto [leftPoint, rightPoint] {calculateHorizontalPoints(row, imageWidth)};
		cv::line(image, leftPoint, rightPoint, gridColor);
	}
	
	drawOuterNorthWall(imageWidth, image);
	drawOuterWestWall(imageHeight, image);
	drawOuterSouthWall(imageWidth, imageHeight, image);
	drawOuterEastWall(imageWidth, imageHeight, image);
	
	cv::imwrite(imagePath, image);
}

std::pair<const cv::Point, const cv::Point> ImageGridVisualizer::calculateVerticalPoints(const int column,
                                                                                         const int imageHeight) const noexcept {
	const auto topPoint {cv::Point(column * cellSize + borderSize, borderSize)};
	const auto bottomPoint {cv::Point(column * cellSize + borderSize, imageHeight - borderSize - 1)};
	
	return {topPoint, bottomPoint};
}

std::pair<const cv::Point, const cv::Point> ImageGridVisualizer::calculateHorizontalPoints(const int row,
                                                                                           const int imageWidth) const noexcept {
	const auto leftPoint {cv::Point(borderSize, row * cellSize + borderSize)};
	const auto rightPoint {cv::Point(imageWidth - borderSize - 1, row * cellSize + borderSize)};
	
	return {leftPoint, rightPoint};
}

void ImageGridVisualizer::drawOuterNorthWall(const int imageWidth, cv::Mat& image) const noexcept {
	const auto leftPoint {cv::Point(borderSize, borderSize)};
	const auto rightPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};
	
	cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageGridVisualizer::drawOuterWestWall(const int imageHeight, cv::Mat& image) const noexcept {
	const auto topPoint {cv::Point(borderSize, borderSize)};
	const auto bottomPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};
	
	cv::line(image, topPoint, bottomPoint, gridColor);
}

void ImageGridVisualizer::drawOuterSouthWall(const int imageWidth,
                                             const int imageHeight,
                                             cv::Mat& image) const noexcept {
	const auto leftPoint {cv::Point(borderSize, imageHeight - borderSize - 1)};
	const auto rightPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};
	
	cv::line(image, leftPoint, rightPoint, gridColor);
}

void ImageGridVisualizer::drawOuterEastWall(const int imageWidth,
                                            const int imageHeight,
                                            cv::Mat& image) const noexcept {
	const auto topPoint {cv::Point(imageWidth - borderSize - 1, borderSize)};
	const auto bottomPoint {cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1)};
	
	cv::line(image, topPoint, bottomPoint, gridColor);
}
}