CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

PROJECT(${CORE_PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

SET(HEADER_FILES
		Include/BinaryTreeMazeGenerator.hpp
		Include/Cell.hpp
		Include/Grid.hpp
		Include/GridVisualizer.hpp
		Include/MazeGenerator.hpp
		Include/SeedGenerator.hpp
		Include/SquareGrid.hpp)

SET(SOURCE_FILES
		Source/Cell.cpp
		Source/Grid.cpp
		Source/BinaryTreeMazeGenerator.cpp
		Source/SeedGenerator.cpp
		Source/MazeGenerator.cpp)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Include/)