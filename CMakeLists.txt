cmake_minimum_required(VERSION 3.27)
project(gameoflife)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR src)
set(VENDOR_DIR vendor)

add_subdirectory("${VENDOR_DIR}/raylib")

file(GLOB_RECURSE SOURCE_FILES 
    "${SOURCE_DIR}/**.cpp" 
    "${SOURCE_DIR}/**.h" 
)

add_executable(gameoflife "${SOURCE_FILES}")

target_include_directories(gameoflife PUBLIC 
    "${SOURCE_DIR}"
    "${VENDOR_DIR}/raylib/src"
)

target_link_libraries(gameoflife 
    raylib
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
)