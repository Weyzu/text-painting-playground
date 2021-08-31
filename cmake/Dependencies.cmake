cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(FetchContent)

# ======= SPDLOG =======
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG de0dbfa3596a18cd70a4619b6a9766847a941276
)
FetchContent_MakeAvailable(spdlog)
# ======================
# ======== FMT =========
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG 7bdf0628b1276379886c7f6dda2cef2b3b374f0b
)
FetchContent_MakeAvailable(fmt)
# ======================

set_target_properties(
	fmt UltralightSDK
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
		LIBRARY_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
)
MACRO(ADD_DEPS)
	set(APP_NAME ${CMAKE_PROJECT_NAME})
	target_link_libraries(${APP_NAME} PRIVATE spdlog)
ENDMACRO()
