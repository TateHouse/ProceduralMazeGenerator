CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		CommandParserTest.cpp
		GridCommandTest.cpp
		InMemoryCommandRepositoryTest.cpp
		QuitCommandTest.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
