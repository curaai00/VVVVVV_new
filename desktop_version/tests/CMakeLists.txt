SET(BINARY VVVVVV_tst)

LINK_DIRECTORIES(/usr/local/lib /usr/local/Cellar/sdl2_mixer/2.0.4/lib)
IF(APPLE)
    include(FindPkgConfig) 	
    PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)
    PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
ELSE()
    find_package(SDL2 CONFIG)
ENDIF()

SET(TEST_SOURCES
    main.cpp
    tst_game.cpp
    )

IF(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # set_property(TARGET ${BINARY} PROPERTY
    #     MSVC_RUNTIME_LIBRARY "MultiThreaded Debug")
    #     # MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug> DLL")
    # message("RUNTIME LIB Setting")
ENDIF()


ADD_EXECUTABLE(${BINARY} ${TEST_SOURCES})
ADD_TEST(NAME ${BINARY} COMMAND ${BINARY})
TARGET_LINK_LIBRARIES(${BINARY} ${SDL2_MIXER_LIBRARIES} VVVVVV_lib gtest )
