CMAKE_MINIMUM_REQUIRED(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

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