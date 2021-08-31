cmake_minimum_required (VERSION 3.12)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(
	TextPainter

	LANGUAGES C CXX
	VERSION 1.0
)

include(cmake/App.cmake)
include(cmake/Dependencies.cmake)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(SOURCES "src/main.cpp")

if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ -g -stdlib=libc++ -Wall -Wno-unknown-attributes")
	set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO)
endif()

add_subdirectory(src)
add_app("${SOURCES}")
add_deps()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
	XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
	CXX_STANDARD 17
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE core)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE common)
