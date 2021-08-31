cmake_minimum_required(VERSION 3.12)

set(CORE_HEADERS
	"include/core/Application.h"
	"include/core/CharacterColors.h"
	"include/core/ColoringService.h"
	"include/core/highlight.h"
	"include/core/UiMessageProcessor.h"
	"include/core/UiOutgoingMessage.h"
	"include/core/UiResponseService.h"
	"include/core/VueStoreProxy.h"
)
set(CORE_SOURCES
	"Application.cpp"
	"ColoringService.cpp"
	"UiOutgoingMessage.cpp"
	"UiResponseService.cpp"
	"VueStoreProxy.cpp"
)

add_library(core STATIC "${CORE_SOURCES}" "${CORE_HEADERS}")

target_include_directories(
	core

	PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_link_libraries(core PRIVATE common)
target_link_libraries(core PRIVATE fmt)
target_link_libraries(core PRIVATE spdlog)

if(APPLE)
	find_library(CocoaLib Cocoa)
endif()

set_property(TARGET core PROPERTY CXX_STANDARD 17)
