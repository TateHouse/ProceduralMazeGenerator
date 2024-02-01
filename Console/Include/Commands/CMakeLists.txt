CMAKE_MINIMUM_REQUIRED(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

SET(HEADER_FILES
		Command.hpp
		CommandFactory.hpp
		CommandParametersUtility.hpp
		CommandParser.hpp
		CommandRepository.hpp
		ExportCommand.hpp
		GridCommand.hpp
		HelpCommand.hpp
		InMemoryCommandRepository.hpp
		MazeCommand.hpp
		ParsedCommandInput.hpp
		QuitCommand.hpp
		VersionCommand.hpp
		VisualizeCommand.hpp)

TARGET_SOURCES(${CONSOLE_LIBRARY_PROJECT_NAME} PRIVATE ${HEADER_FILES})
TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
