#pragma once

#include <opencv2/opencv.hpp>

#include <string>

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ImageGridVisualizer : public Core::GridVisualizer {
public:
	explicit ImageGridVisualizer(const Core::Grid* const grid, const int cellSize, const int borderSize,
	                             const std::string_view imagePath,
	                             const cv::Scalar& backgroundColor,
	                             const cv::Scalar& gridColor);
	
	virtual void display() noexcept override;

private:
	std::pair<const cv::Point, const cv::Point> calculateVerticalPoints(const int column,
	                                                                    const int imageHeight) const noexcept;
	std::pair<const cv::Point, const cv::Point> calculateHorizontalPoints(const int row,
	                                                                      const int imageWidth) const noexcept;
	
	void drawOuterNorthWall(const int imageWidth, cv::Mat& image) const noexcept;
	void drawOuterWestWall(const int imageHeight, cv::Mat& image) const noexcept;
	void drawOuterSouthWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept;
	void drawOuterEastWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept;

private:
	const Core::Grid* const grid;
	const int cellSize;
	const int borderSize;
	const std::string imagePath;
	const cv::Scalar backgroundColor;
	const cv::Scalar gridColor;
};
}