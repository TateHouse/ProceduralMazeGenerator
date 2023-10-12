CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		BinaryTreeMazeGenerator.hpp
		Cell.hpp
		Grid.hpp
		GridVisualizer.hpp
		MazeGenerator.hpp
		SeedGenerator.hpp
		SquareGrid.hpp)

TARGET_SOURCES(${PROJECT_NAME} PUBLIC ${HEADER_FILES})