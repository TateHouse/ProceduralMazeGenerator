CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		ConsoleGridVisualizer.hpp
		ConsoleMazeVisualizer.hpp
		ImageGridVisualizer.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})