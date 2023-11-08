CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		Command.hpp
		CommandParser.hpp
		CommandRepository.hpp
		InMemoryCommandRepository.hpp
		ParsedCommandInput.hpp
		QuitCommand.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
