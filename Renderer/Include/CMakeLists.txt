CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		Shader.hpp
		ShaderCompilationException.hpp
		ShaderLinkingException.hpp
		ShaderTypeStringConverter.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})

ADD_SUBDIRECTORY(Utility)