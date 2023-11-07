CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(SOURCE_FILES
		FragmentShader.cpp
		GeometryShader.cpp
		Shader.cpp
		ShaderProgram.cpp
		VertexShader.cpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
