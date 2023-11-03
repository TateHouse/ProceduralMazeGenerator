CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		Application.hpp
		CellSettings.hpp
		Component.hpp
		Context.hpp
		InputComponent.hpp
		Maze.hpp
		OrthographicCamera.hpp
		OrthographicCameraDefaults.hpp
		OrthographicCameraInput.hpp
		Window.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})

ADD_SUBDIRECTORY(Shader)
ADD_SUBDIRECTORY(Utility)