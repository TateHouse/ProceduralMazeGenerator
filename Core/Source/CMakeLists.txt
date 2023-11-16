CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		AldousBroderMazeGenerator.cpp
		BinaryTreeMazeGenerator.cpp
		Cell.cpp
		SquareGrid.cpp
		ImageVisualizer.cpp
		ImageVisualizerBuilder.cpp
		MazeGenerator.cpp
		SeedGenerator.cpp
		SidewinderMazeGenerator.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})