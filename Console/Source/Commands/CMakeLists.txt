CMAKE_MINIMUM_REQUIRED(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

SET(SOURCE_FILES
		Command.cpp
		CommandFactory.cpp
		CommandParser.cpp
		CommandParserUtility.cpp
		CommandRepository.cpp
		ExportCommand.cpp
		GridCommand.cpp
		HelpCommand.cpp
		InMemoryCommandRepository.cpp
		MazeCommand.cpp
		ParsedCommandInput.cpp
		QuitCommand.cpp
		VersionCommand.cpp
		VisualizeCommand.cpp)

TARGET_SOURCES(${CONSOLE_LIBRARY_PROJECT_NAME} PRIVATE ${SOURCE_FILES})
TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
