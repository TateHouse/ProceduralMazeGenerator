CMAKE_MINIMUM_REQUIRED(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

PROJECT(${TEST_PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

SET(ENTRY_POINT
		Source/Core/Main.cpp)

ADD_EXECUTABLE(${TEST_PROJECT_NAME} ${ENTRY_POINT})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Include/)

FIND_PACKAGE(GTest CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gmock)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE ${CORE_PROJECT_NAME})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE ${CONSOLE_LIBRARY_PROJECT_NAME})

ADD_SUBDIRECTORY(Include)
ADD_SUBDIRECTORY(Source)