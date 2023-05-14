cmake_minimum_required(VERSION 3.26)

project("didah")

file(GLOB SRCS src/*.c)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} /usr/include)
include_directories(${SDL_MIXER_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} SDL2_mixer)