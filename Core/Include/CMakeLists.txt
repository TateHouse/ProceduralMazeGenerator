CMAKE_MINIMUM_REQUIRED(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

SET(HEADER_FILES
		AldousBroderMazeGenerator.hpp
		BinaryTreeMazeGenerator.hpp
		Cell.hpp
		Grid.hpp
		GridVisualizer.hpp
		ImageVisualizer.hpp
		ImageVisualizerBuilder.hpp
		MazeGenerator.hpp
		SeedGenerator.hpp
		SidewinderMazeGenerator.hpp
		SquareGrid.hpp
		WilsonsMazeGenerator.hpp)

TARGET_SOURCES(${PROJECT_NAME} PUBLIC ${HEADER_FILES})