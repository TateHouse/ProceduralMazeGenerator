#pragma once

#include <opencv2/opencv.hpp>

#include <filesystem>

#include "Grid.hpp"
#include "GridVisualizer.hpp"
#include "ImageVisualizerBuilder.hpp"

namespace Core {
/**
 * @brief Visualizes a grid as a PNG image.
 * @class ImageVisualizer
 */
class ImageVisualizer final : public Core::GridVisualizer {
public:
	/**
	 * @brief Instantiates a new image visualizer builder.
	 * @param grid The grid to visualize.
	 * @param imagePath The path to the image to save.
	 * @return The new image visualizer builder.
	 */
    static ImageVisualizerBuilder create(const Core::Grid* const grid, const std::filesystem::path& imagePath);

private:
	/**
	 * @brief Instantiates a new image visualizer.
	 * @param grid The grid to visualize.
	 * @param imagePath The path to the image to save.
	 * @param cellSize The size of each cell in the image.
	 * @param borderSize The size of the border around each cell in the image.
	 * @param backgroundColor The background color of the image.
	 * @param gridColor The color of the grid in the image.
	 */
    ImageVisualizer(const Core::Grid* const grid,
                    const std::filesystem::path& imagePath,
                    const int cellSize,
                    const int borderSize,
                    const cv::Scalar& backgroundColor,
                    const cv::Scalar& gridColor);

public:
	/**
	 * @brief Instantiates a new image visualizer by copying the given image visualizer.
	 * @param other The image visualizer to copy.
	 */
    ImageVisualizer(const ImageVisualizer& other) = default;
	
	/**
	 * @brief Instantiates a new image visualizer by moving the given image visualizer.
	 * @param other The image visualizer to move.
	 */
    ImageVisualizer(ImageVisualizer&& other) noexcept = default;
	
	/**
	 * @brief Destroys the image visualizer.
	 */
    ~ImageVisualizer() noexcept override = default;

public:
	/**
	 * @brief Assigns the given image visualizer to this image visualizer using copy semantics.
	 * @param other The image visualizer to copy.
	 * @return A reference to this image visualizer.
	 */
    ImageVisualizer& operator=(const ImageVisualizer& other) = delete;
	
	/**
	 * @brief Assigns the given image visualizer to this image visualizer using move semantics.
	 * @param other The image visualizer to move.
	 * @return A reference to this image visualizer.
	 */
    ImageVisualizer& operator=(ImageVisualizer&& other) noexcept = delete;

public:
    void visualize() const noexcept override;

private:
	/**
	 * @brief Calculates the points of the vertical line of the given cell.
	 * @param isFirstRow Whether or not the cell is in the first row.
	 * @param topLeftX The x position of the top left corner of the cell.
	 * @param topLeftY The y position of the top left corner of the cell.
	 * @return
	 */
    [[nodiscard]] std::pair<const cv::Point, const cv::Point> calculateVerticalPoints(const bool isFirstRow,
                                                                                      const int topLeftX,
                                                                                      const int topLeftY) const noexcept;
	
	/**
	 * @brief Calculates the points of the horizontal line of the given cell.
	 * @param isLastColumn Whether or not the cell is in the last column.
	 * @param topLeftX The x position of the top left corner of the cell.
	 * @param topLeftY The y position of the top left corner of the cell.
	 * @return
	 */
    [[nodiscard]] std::pair<const cv::Point, const cv::Point> calculateHorizontalPoints(const bool isLastColumn,
                                                                                        const int topLeftX,
                                                                                        const int topLeftY) const noexcept;

	/**
	 * @brief Draws the outer north wall of the maze.
	 * @param imageWidth The width of the image.
	 * @param image The image to draw on.
	 */
    void drawOuterNorthWall(const int imageWidth, cv::Mat& image) const noexcept;
	
	/**
	 * @brief Draws the outer west wall of the maze.
	 * @param imageHeight The height of the image.
	 * @param image The image to draw on.
	 */
    void drawOuterWestWall(const int imageHeight, cv::Mat& image) const noexcept;
	
	/**
	 * @brief Draws the outer south wall of the maze.
	 * @param imageWidth The width of the image.
	 * @param imageHeight The height of the image.
	 * @param image The image to draw on.
	 */
    void drawOuterSouthWall(const int imageWidth, const int imageHeight, cv::Mat& image) const noexcept;
	
	/**
	 * @brief Draws the outer east wall of the maze.
	 * @param imageWidth The width of the image.
	 * @param imageHeight The height of the image.
	 * @param image The image to draw on.
	 */
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