CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		Command.cpp
		CommandFactory.cpp
		CommandParser.cpp
		CommandParserUtility.cpp
		CommandRepository.cpp
		ExportCommand.cpp
		GridCommand.cpp
		InMemoryCommandRepository.cpp
		MazeCommand.cpp
		ParsedCommandInput.cpp
		QuitCommand.cpp)

TARGET_SOURCES(${CONSOLE_LIBRARY_PROJECT_NAME} PRIVATE ${SOURCE_FILES})
TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
