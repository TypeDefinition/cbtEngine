cmake_minimum_required(VERSION 3.16.3)

project("cbtEngine")

# cbtCore
set(CBT_CORE_SRC_DIR "src/cbtCore")
file(GLOB_RECURSE CBT_CORE_SRC LIST_DIRECTORIES true CONFIGURE_DEPENDS
        "${CBT_CORE_SRC_DIR}/*.h"
        "${CBT_CORE_SRC_DIR}/*.c"
        "${CBT_CORE_SRC_DIR}/*.hpp"
        "${CBT_CORE_SRC_DIR}/*.cpp")
add_library("cbtCore" ${CBT_CORE_SRC} src/cbtCore/Core/Math/cbtPhysicsUtil.h src/cbtCore/Core/Math/cbtPhysicsUtil.cpp)

target_include_directories("cbtCore" PUBLIC ${CBT_CORE_SRC_DIR})
target_link_libraries("cbtCore" "GL" "GLEW" "SDL2" "SDL2_image")

# cbtGame
set(CBT_GAME_SRC_DIR "src/cbtGame")
file(GLOB_RECURSE CBT_GAME_SRC LIST_DIRECTORIES true CONFIGURE_DEPENDS
        "${CBT_GAME_SRC_DIR}/*.h"
        "${CBT_GAME_SRC_DIR}/*.c"
        "${CBT_GAME_SRC_DIR}/*.hpp"
        "${CBT_GAME_SRC_DIR}/*.cpp")
add_executable("cbtGame" ${CBT_GAME_SRC})

target_include_directories("cbtGame" PUBLIC ${CBT_CORE_SRC_DIR} PUBLIC ${CBT_GAME_SRC_DIR})
target_link_libraries("cbtGame" "cbtCore" "GL" "GLEW" "SDL2" "SDL2_image")
