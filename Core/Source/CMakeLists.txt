CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

SET(SOURCE_FILES
		AldousBroderMazeGenerator.cpp
		BinaryTreeMazeGenerator.cpp
		Cell.cpp
		ImageVisualizer.cpp
		ImageVisualizerBuilder.cpp
		MazeGenerator.cpp
		SeedGenerator.cpp
		SidewinderMazeGenerator.cpp
		SquareGrid.cpp
		WilsonsMazeGenerator.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})