cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMONLIB_HEADERS
	"${CMAKE_CURRENT_BINARY_DIR}/include/*.h"
)

add_library(common STATIC
	"config/ConfigurationProvider.cpp"
	"infrastructure/UltralightLogger.cpp"
	"utilities/JsonParsing.cpp"
	"${COMMONLIB_HEADERS}"
)

target_include_directories(
	common

	PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_link_libraries(common PUBLIC core)
target_link_libraries(common PRIVATE spdlog)
target_link_libraries(common PRIVATE fmt)
target_include_directories(common PUBLIC "${ULTRALIGHT_INCLUDE_DIR}")

set_property(TARGET common PROPERTY CXX_STANDARD 17)
