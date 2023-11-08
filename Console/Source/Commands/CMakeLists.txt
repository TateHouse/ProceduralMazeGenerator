CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		Command.cpp
		CommandParser.cpp
		CommandRepository.cpp
		InMemoryCommandRepository.cpp
		ParsedCommandInput.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
