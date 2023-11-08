CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		Command.hpp
		CommandInterpreter.hpp
		CommandRepository.hpp
		InMemoryCommandRepository.hpp
		ParsedCommandInput.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
