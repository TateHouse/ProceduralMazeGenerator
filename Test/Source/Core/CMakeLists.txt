CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		BinaryTreeMazeGeneratorTest.cpp
		CellAttributeTest.cpp
		CellLinkingTest.cpp
		SquareGridTest.cpp
		MazeGeneratorTest.cpp
		SidewinderMazeGeneratorTest.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})