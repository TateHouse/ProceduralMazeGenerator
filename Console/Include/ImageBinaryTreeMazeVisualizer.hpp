#pragma once

#include <opencv2/opencv.hpp>

#include <string>

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ImageBinaryTreeMazeVisualizer : public Core::GridVisualizer {
public:
	explicit ImageBinaryTreeMazeVisualizer(const Core::Grid* const grid,
	                                       const unsigned int cellSize,
	                                       const unsigned int borderSize,
	                                       const std::string_view imagePath,
	                                       const cv::Scalar& backgroundColor,
	                                       const cv::Scalar& gridColor);
	
	virtual void display() noexcept override;

private:
	const Core::Grid* const grid;
	const unsigned int cellSize;
	const unsigned int borderSize;
	const std::string imagePath;
	const cv::Scalar backgroundColor;
	const cv::Scalar gridColor;
};
}