cmake_minimum_required(VERSION 2.6)

project(Roombal)
set(EXECUTABLE_NAME "Roomball")

file(
	GLOB_RECURSE
	SRCS

	src/*
)

add_executable(
	${EXECUTABLE_NAME}
	${SRCS}
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(SFML 2.3.2 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})