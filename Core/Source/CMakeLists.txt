CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		BinaryTreeMazeGenerator.cpp
		Cell.cpp
		Grid.cpp
		MazeGenerator.cpp
		SeedGenerator.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})