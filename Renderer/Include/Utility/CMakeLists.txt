CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

SET(HEADER_FILES
		CameraManager.hpp
		DeltaTimeManager.hpp
		FileLoader.hpp
		UnitScale.hpp
		WindowManager.hpp)

TARGET_SOURCES(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
