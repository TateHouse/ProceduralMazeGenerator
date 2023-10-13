CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		ConsoleGridVisualizer.cpp
		ConsoleMazeVisualizer.cpp
		ImageGridVisualizer.cpp
		ImageBinaryTreeMazeVisualizer.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
