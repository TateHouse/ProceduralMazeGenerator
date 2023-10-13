#include "ImageGridVisualizer.hpp"

namespace Console {
ImageGridVisualizer::ImageGridVisualizer(const Core::Grid* const grid,
                                         const unsigned int cellSize,
                                         const unsigned int borderSize,
                                         const std::string_view imagePath,
                                         const cv::Scalar& backgroundColor,
                                         const cv::Scalar& gridColor) :
		grid {grid},
		cellSize {cellSize},
		borderSize {borderSize},
		imagePath {imagePath.data()},
		backgroundColor {backgroundColor},
		gridColor {gridColor} {
	if (borderSize < 1) {
		throw std::invalid_argument {"Border size must be greater than 0."};
	}
}

void ImageGridVisualizer::display() noexcept {
	const auto [gridWidth, gridHeight] {grid->getSize()};
	
	const auto imageWidth {static_cast<int>(cellSize * gridWidth + (2 * borderSize))};
	const auto imageHeight {static_cast<int>(cellSize * gridHeight + (2 * borderSize))};
	
	auto image {cv::Mat {imageHeight, imageWidth, CV_8UC3, backgroundColor}};
	
	for (std::size_t x {1}; x < gridWidth; ++x) {
		const auto topPoint {cv::Point {static_cast<int>(x * cellSize + borderSize), static_cast<int>(borderSize)}};
		const auto bottomPoint {cv::Point {static_cast<int>(x * cellSize + borderSize),
		                                   static_cast<int>(imageHeight - borderSize - 1)}};
		cv::line(image, topPoint, bottomPoint, gridColor);
	}
	
	for (std::size_t y {1}; y < gridHeight; ++y) {
		const auto leftPoint {cv::Point {static_cast<int>(borderSize), static_cast<int>(y * cellSize + borderSize)}};
		const auto rightPoint {cv::Point {static_cast<int>(imageWidth - borderSize - 1),
		                                  static_cast<int>(y * cellSize + borderSize)}};
		cv::line(image, leftPoint, rightPoint, gridColor);
	}
	
	// Drawing outer walls
	cv::line(image, cv::Point(borderSize, borderSize), cv::Point(imageWidth - borderSize - 1, borderSize), gridColor);
	cv::line(image, cv::Point(borderSize, borderSize), cv::Point(borderSize, imageHeight - borderSize - 1), gridColor);
	cv::line(image,
	         cv::Point(borderSize, imageHeight - borderSize - 1),
	         cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1),
	         gridColor);
	cv::line(image,
	         cv::Point(imageWidth - borderSize - 1, borderSize),
	         cv::Point(imageWidth - borderSize - 1, imageHeight - borderSize - 1),
	         gridColor);
	
	cv::imwrite(imagePath, image);
}
}