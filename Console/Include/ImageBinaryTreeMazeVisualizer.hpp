#pragma once

#include <opencv2/opencv.hpp>

#include <string>

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ImageBinaryTreeMazeVisualizer : public Core::GridVisualizer {
public:
	explicit ImageBinaryTreeMazeVisualizer(const Core::Grid* const grid, const int cellSize, const int borderSize,
	                                       const std::string_view imagePath,
	                                       const cv::Scalar& backgroundColor,
	                                       const cv::Scalar& gridColor);
	
	virtual void visualize() noexcept override;

private:
	std::pair<const cv::Point, const cv::Point> calculateVerticalPoints(const bool isFirstRow,
	                                                                    const int topLeftX,
	                                                                    const int topLeftY) const noexcept;
	std::pair<const cv::Point, const cv::Point> calculateHorizontalPoints(const bool isLastColumn, const int topLeftX,
	                                                                      const int topLeftY) const noexcept;
	void drawOuterNorthWall(const int imageWidth, const cv::Mat& image) const noexcept;
	void drawOuterWestWall(const int imageHeight, const cv::Mat& image) const noexcept;
	void drawOuterSouthWall(const int imageWidth, int imageHeight, const cv::Mat& image) const noexcept;
	void drawOuterEastWall(const int imageWidth, int imageHeight, const cv::Mat& image) const noexcept;

private:
	const Core::Grid* const grid;
	const int cellSize;
	const int borderSize;
	const std::string imagePath;
	const cv::Scalar backgroundColor;
	const cv::Scalar gridColor;
};
}