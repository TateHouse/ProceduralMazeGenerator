CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		FragmentShader.hpp
		GeometryShader.hpp
		Shader.hpp
		ShaderProgram.hpp
		VertexShader.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})