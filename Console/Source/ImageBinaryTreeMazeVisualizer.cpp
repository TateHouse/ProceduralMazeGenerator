#include "ImageBinaryTreeMazeVisualizer.hpp"

namespace Console {
ImageBinaryTreeMazeVisualizer::ImageBinaryTreeMazeVisualizer(const Core::Grid* const grid,
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

void ImageBinaryTreeMazeVisualizer::display() noexcept {
	const auto [gridWidth, gridHeight] {grid->getSize()};
	
	const auto imageWidth {static_cast<int>(cellSize * gridWidth + (2 * borderSize))};
	const auto imageHeight {static_cast<int>(cellSize * gridHeight + (2 * borderSize))};
	
	auto image {cv::Mat {imageHeight, imageWidth, CV_8UC3, backgroundColor}};
	
	for (auto row {gridHeight - 1}; row >= 0; --row) {
		for (std::size_t column {0}; column < gridWidth; ++column) {
			const auto position {std::pair<const int, const int> {static_cast<int>(column), row}};
			const auto* const cell {(*grid)[position]};
			
			auto topLeftY {static_cast<int>(imageHeight - (row + 1) * cellSize - borderSize)};
			auto topLeftX {static_cast<int>(column * cellSize + borderSize)};
			
			const auto* const eastNeighbor {cell->getEast()};
			const auto* const southNeighbor {cell->getSouth()};
			
			if (column != gridWidth - 1 && (eastNeighbor == nullptr || !cell->isLinked(eastNeighbor))) {
				auto adjustedTopLeftY {topLeftY};
				if (row == 0) {
					adjustedTopLeftY -= 1;
				}
				
				const auto topPoint {cv::Point {static_cast<int>(topLeftX + cellSize), topLeftY}};
				const auto bottomPoint {cv::Point {static_cast<int>(topLeftX + cellSize),
				                                   static_cast<int>(adjustedTopLeftY + cellSize)}};
				cv::line(image, topPoint, bottomPoint, gridColor);
			}
			
			if (row != 0 && (southNeighbor == nullptr || !cell->isLinked(southNeighbor))) {
				const auto leftPoint {cv::Point {topLeftX, static_cast<int>(topLeftY + cellSize)}};
				const auto rightPoint {cv::Point {static_cast<int>(topLeftX + cellSize),
				                                  static_cast<int>(topLeftY + cellSize)}};
				cv::line(image, leftPoint, rightPoint, gridColor);
			}
		}
	}
	
	cv::line(image,
	         cv::Point(borderSize, borderSize),
	         cv::Point(static_cast<int>(imageWidth - borderSize - 1), borderSize),
	         gridColor);
	cv::line(image,
	         cv::Point(borderSize, borderSize),
	         cv::Point(borderSize, static_cast<int>(imageHeight - (borderSize + 1))),
	         gridColor);
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