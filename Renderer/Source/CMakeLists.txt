CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		MazeRenderer.cpp
		Shader.cpp
		ShaderCompilationException.cpp
		ShaderLinkingException.cpp
		ShaderTypeStringConverter.cpp
		Window.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

ADD_SUBDIRECTORY(Utility)