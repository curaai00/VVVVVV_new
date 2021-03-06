cmake_minimum_required(VERSION 3.10.2)

# CMake Options
OPTION(ENABLE_WARNINGS "Enable compilation warnings" OFF)
OPTION(ENABLE_WERROR "Treat compilation warnings as errors" OFF)

SET(CUSTOM_LEVEL_SUPPORT ENABLED CACHE STRING "Optionally disable playing and/or editing of custom levels")
SET_PROPERTY(CACHE CUSTOM_LEVEL_SUPPORT PROPERTY STRINGS ENABLED NO_EDITOR DISABLED)

SET(STEAM OFF CACHE BOOL "Use the Steam API")
SET(GOG OFF CACHE BOOL "Use the GOG API")

IF(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	SET(STEAM ON)
	SET(GOG ON)
ENDIF()

# SET(CMAKE_CXX_EXTENSIONS OFF) # prevent mixing stdlib implementations (dangerous!)

# Architecture Flags
IF(APPLE)
	# Wow, Apple is a huge jerk these days huh?
	SET(OSX_10_9_SDK_PATH /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk)
	IF(NOT CMAKE_OSX_SYSROOT)
		IF(IS_DIRECTORY ${OSX_10_9_SDK_PATH})
			SET(CMAKE_OSX_SYSROOT ${OSX_10_9_SDK_PATH})
		ELSE()
			MESSAGE(WARNING "CMAKE_OSX_SYSROOT not set and macOS 10.9 SDK not found! Using default one.")
		ENDIF()
	ENDIF()
	SET(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
	LINK_DIRECTORIES(/usr/local/lib)
	ADD_COMPILE_OPTIONS(-Werror=partial-availability)
ENDIF()

SET(exec VVVVVV_run)
SET(vvv_lib VVVVVV_lib)

IF(APPLE)
	MESSAGE(STATUS "Using macOS SDK at ${CMAKE_OSX_SYSROOT}")
ENDIF()

# Compiler Flags
ADD_DEFINITIONS(-DPHYSFS_SUPPORTS_DEFAULT=0 -DPHYSFS_SUPPORTS_ZIP=1)

# RPATH
IF(NOT WIN32)
	IF(APPLE)
		SET(BIN_LIBROOT "osx")
		SET(BIN_RPATH "@executable_path/osx")
	ELSEIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
		SET(BIN_LIBROOT "lib64")
		SET(BIN_RPATH "\$ORIGIN/lib64")
	ELSE()
		SET(BIN_LIBROOT "lib")
		SET(BIN_RPATH "\$ORIGIN/lib")
	ENDIF()
	SET(CMAKE_SKIP_BUILD_RPATH TRUE)
	SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
	SET(CMAKE_INSTALL_RPATH ${BIN_RPATH})
	SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
ENDIF()

# Include Directories
INCLUDE_DIRECTORIES(
	../../third_party/tinyxml2
	../../third_party/physfs
	../../third_party/lodepng
	../../third_party/utfcpp/source
	../../third_party/nlohmann
)

# Source Lists
FILE(GLOB_RECURSE VVV_SRC LIST_DIRECTORIES false *.h *.c *.cpp)
message(${VVV_SRC})
list(FILTER VVV_SRC EXCLUDE REGEX ".*src/main.cpp$")


IF(NOT CUSTOM_LEVEL_SUPPORT STREQUAL "DISABLED")
	LIST(APPEND VVV_SRC editor.cpp)
ENDIF()
IF(STEAM)
	LIST(APPEND VVV_SRC SteamNetwork.c)
	ADD_DEFINITIONS(-DSTEAM_NETWORK)
ENDIF()
IF(GOG)
	LIST(APPEND VVV_SRC GOGNetwork.c)
	ADD_DEFINITIONS(-DGOG_NETWORK)
ENDIF()

SET(XML2_SRC
	../../third_party/tinyxml2/tinyxml2.cpp
)
SET(PFS_SRC
	../../third_party/physfs/physfs.c
	../../third_party/physfs/physfs_archiver_dir.c
	../../third_party/physfs/physfs_archiver_unpacked.c
	../../third_party/physfs/physfs_archiver_zip.c
	../../third_party/physfs/physfs_byteorder.c
	../../third_party/physfs/physfs_unicode.c
	../../third_party/physfs/physfs_platform_posix.c
	../../third_party/physfs/physfs_platform_unix.c
	../../third_party/physfs/physfs_platform_windows.c
	../../third_party/physfs/physfs_platform_haiku.cpp
)
IF(APPLE)
	# Are you noticing a pattern with this Apple crap yet?
	SET(PFS_SRC ${PFS_SRC} ../../third_party/physfs/physfs_platform_apple.m)
ENDIF()
SET(PNG_SRC ../../third_party/lodepng/lodepng.c)

# Executable information
ADD_LIBRARY(${vvv_lib} ${VVV_SRC})

# Build options
IF(ENABLE_WARNINGS)
	# The weird syntax is due to CMake generator expressions.
	# Saves quite a few lines and boilerplate at the price of readability.
	TARGET_COMPILE_OPTIONS(${vvv_lib} PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
			-Wall $<$<BOOL:${ENABLE_WERROR}>:-Werror>>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4 $<$<BOOL:${ENABLE_WERROR}>:/WX>>)
ENDIF()

IF(CUSTOM_LEVEL_SUPPORT STREQUAL "NO_EDITOR")
	ADD_DEFINITIONS(-DNO_EDITOR)
ELSEIF(CUSTOM_LEVEL_SUPPORT STREQUAL "DISABLED")
	ADD_DEFINITIONS(-DNO_CUSTOM_LEVELS -DNO_EDITOR)
ENDIF()

IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	SET(SUPPORTS_IMPLICIT_FALLTHROUGH 1)
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	IF(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
		SET(SUPPORTS_IMPLICIT_FALLTHROUGH 1)
	ELSE()
		SET(SUPPORTS_IMPLICIT_FALLTHROUGH 0)
	ENDIF()
ELSE()
	SET(SUPPORTS_IMPLICIT_FALLTHROUGH 0)
ENDIF()


IF(SUPPORTS_IMPLICIT_FALLTHROUGH)
	TARGET_COMPILE_OPTIONS(${vvv_lib} PRIVATE -Werror=implicit-fallthrough)
ENDIF()

# Library information
ADD_LIBRARY(tinyxml2-static STATIC ${XML2_SRC})
ADD_LIBRARY(physfs-static STATIC ${PFS_SRC} ${PFSP_SRC})
ADD_LIBRARY(lodepng-static STATIC ${PNG_SRC})

# Static Dependencies
TARGET_LINK_LIBRARIES(${vvv_lib} physfs-static tinyxml2-static lodepng-static)

# SDL2 Dependency (Detection pulled from FAudio)
if (DEFINED SDL2_INCLUDE_DIRS AND DEFINED SDL2_LIBRARIES)
	message(STATUS "Using pre-defined SDL2 variables SDL2_INCLUDE_DIRS and SDL2_LIBRARIES")
	target_include_directories(${vvv_lib} PUBLIC "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>")
	target_link_libraries(${vvv_lib} ${SDL2_LIBRARIES})
else()
	# Only try to autodetect if both SDL2 variables aren't explicitly set
	IF(APPLE)
		include(FindPkgConfig) 	
		PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)
		PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
		message(${SDL2_MIXER_LIBRARIES})
	ELSE()
		find_package(SDL2 CONFIG)
	ENDIF()

	if (TARGET SDL2::SDL2)
		message(STATUS "Using TARGET SDL2::SDL2")
		target_link_libraries(${vvv_lib} PUBLIC SDL2::SDL2 SDL2_mixer)
	elseif (TARGET SDL2)
		message(STATUS "Using TARGET SDL2")
		target_link_libraries(${vvv_lib} PUBLIC SDL2 SDL2_mixer)
	else()
		message(STATUS "No TARGET SDL2::SDL2, or SDL2, using variables")
		find_path(SDL2_MIXER_INCLUDE_DIRS NAMES SDL_mixer.h PATH_SUFFIXES SDL2)
		target_include_directories(${vvv_lib} PUBLIC "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>" ${SDL2_MIXER_INCLUDE_DIRS})
		target_link_libraries(${vvv_lib} SDL2_mixer ${SDL2_LIBRARIES})
	endif()
endif()

# Yes, more Apple Crap
IF(APPLE)
	FIND_LIBRARY(FOUNDATION NAMES Foundation)
	FIND_LIBRARY(IOKIT NAMES IOKit)
	TARGET_LINK_LIBRARIES(${vvv_lib} objc ${IOKIT} ${FOUNDATION})
ENDIF()
# But hey, also some Haiku crap
IF(HAIKU)
	FIND_LIBRARY(BE_LIBRARY be)
	FIND_LIBRARY(ROOT_LIBRARY root)
	TARGET_LINK_LIBRARIES(${vvv_lib} ${BE_LIBRARY} ${ROOT_LIBRARY})
ENDIF()

IF(WIN32)
	# ADD_EXECUTABLE(VVVVVV ${VVV_SRC})
	add_executable(${exec} WIN32 main.cpp)
ELSE()
	# ADD_EXECUTABLE(VVVVVV ${VVV_SRC})
	add_executable(${exec} main.cpp)
ENDIF()

target_link_libraries(${exec} PRIVATE ${vvv_lib})

