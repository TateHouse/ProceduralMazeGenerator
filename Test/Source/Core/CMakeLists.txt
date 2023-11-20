CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		AldousBroderMazeGeneratorTest.cpp
		BinaryTreeMazeGeneratorTest.cpp
		CellAttributeTest.cpp
		CellLinkingTest.cpp
		MazeGeneratorTest.cpp
		SidewinderMazeGeneratorTest.cpp
		SquareGridTest.cpp
		WilsonsMazeGeneratorTest.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})