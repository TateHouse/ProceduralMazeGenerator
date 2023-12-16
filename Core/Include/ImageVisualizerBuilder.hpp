#pragma once

#include <opencv2/core.hpp>

#include <filesystem>
#include <memory>

#include "Grid.hpp"

namespace Core {
/**
 * @brief Builds an image visualizer.
 * @class ImageVisualizerBuilder
 */
class ImageVisualizer;

class ImageVisualizerBuilder final {
public:
	/**
	 * @brief Instantiates a new image visualizer builder.
	 * @param grid The grid to visualize.
	 * @param imagePath The path to the image to save.
	 * @throws std::invalid_argument Thrown if the grid is null.
	 * @throws std::filesystem::filesystem_error Thrown if the directory path is invalid.
	 */
    ImageVisualizerBuilder(const Core::Grid* const grid, const std::filesystem::path& imagePath);
	
	/**
	 * @brief Instantiates a new image visualizer builder by copying the given image visualizer builder.
	 */
    ImageVisualizerBuilder(const ImageVisualizerBuilder&) = delete;
	
	/**
	 * @brief Instantiates a new image visualizer builder by moving the given image visualizer builder.
	 */
    ImageVisualizerBuilder(ImageVisualizerBuilder&&) = delete;
	
	/**
	 * @brief Destroys the image visualizer builder.
	 */
    ~ImageVisualizerBuilder() noexcept = default;

public:
	/**
	 * @brief Assigns the given image visualizer builder to this image visualizer builder using copy semantics.
	 * @return A reference to this image visualizer builder.
	 */
    ImageVisualizerBuilder& operator=(const ImageVisualizerBuilder&) = delete;
	
	/**
	 * @brief Assigns the given image visualizer builder to this image visualizer builder using move semantics.
	 * @return A reference to this image visualizer builder.
	 */
    ImageVisualizerBuilder& operator=(ImageVisualizerBuilder&&) = delete;

public:
	/**
	 * @brief Sets the cell size of the image.
	 * @param cellSize The cell size of the image.
	 * @return A reference to this image visualizer builder.
	 * @throws std::invalid_argument Thrown if the cell size is less than or equal to 0.
	 */
    ImageVisualizerBuilder& setCellSize(const int cellSize);
	
	/**
	 * @brief Sets the border size of the image.
	 * @param borderSize The border size of the image.
	 * @return A reference to this image visualizer builder.
	 * @throws std::invalid_argument Thrown if the border size is negative.
	 */
    ImageVisualizerBuilder& setBorderSize(const int borderSize);
	
	/**
	 * @brief Sets the background color of the image.
	 * @param backgroundColor The background color of the image.
	 * @return A reference to this image visualizer builder.
	 */
    ImageVisualizerBuilder& setBackgroundColor(const cv::Scalar& backgroundColor);
	
	/**
	 * @brief Sets the grid color of the image.
	 * @param gridColor The grid color of the image.
	 * @return A reference to this image visualizer builder.
	 */
    ImageVisualizerBuilder& setGridColor(const cv::Scalar& gridColor);
	
	/**
	 * @brief Builds the image visualizer.
	 * @return The image visualizer.
	 */
    std::unique_ptr<ImageVisualizer> build();

private:
    const Core::Grid* const grid;
    const std::filesystem::path& imagePath;
    int cellSize {5};
    int borderSize {0};
    cv::Scalar backgroundColor {255.0f, 255.0f, 255.0f};
    cv::Scalar gridColor {0.0f, 0.0f, 0.0f};
};
}