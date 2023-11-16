CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		AldousBroderMazeGenerator.hpp
		BinaryTreeMazeGenerator.hpp
		Cell.hpp
		SquareGrid.hpp
		Grid.hpp
		GridVisualizer.hpp
		ImageVisualizer.hpp
		ImageVisualizerBuilder.hpp
		MazeGenerator.hpp
		SeedGenerator.hpp
		SidewinderMazeGenerator.hpp
)

TARGET_SOURCES(${PROJECT_NAME} PUBLIC ${HEADER_FILES})