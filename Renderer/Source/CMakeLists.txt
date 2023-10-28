CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		Application.cpp
		CellSettings.cpp
		Context.cpp
		Maze.cpp
		OrthographicCamera.cpp
		Window.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

ADD_SUBDIRECTORY(Shader)
ADD_SUBDIRECTORY(Utility)