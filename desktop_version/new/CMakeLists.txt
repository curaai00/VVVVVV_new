SET(BINARY VVVVVV_new)

LINK_DIRECTORIES(/usr/local/lib /usr/local/Cellar/sdl2_mixer/2.0.4/lib)
IF(APPLE)
    include(FindPkgConfig) 	
    PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)
    PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
    PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
ELSE()
    find_package(SDL2 CONFIG)
ENDIF()

FILE(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.c *.cpp)
list(FILTER VVV_SRC EXCLUDE REGEX ".*new/main.cpp$")

INCLUDE_DIRECTORIES(
	../../third_party/tinyxml2
	../../third_party/physfs
	../../third_party/lodepng
    ../../third_party/utfcpp/source
    ../../third_party/nlohmann
)
include_directories(${SDL2_INCLUDE_DIRS})


ADD_LIBRARY(${BINARY}lib ${SOURCES})
TARGET_LINK_LIBRARIES(${BINARY}lib ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} VVVVVV_lib )

ADD_EXECUTABLE(${BINARY} main.cpp)
TARGET_LINK_LIBRARIES(${BINARY} ${BINARY}lib)
