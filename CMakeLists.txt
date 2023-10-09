cmake_minimum_required(VERSION 3.25)
project(ArrowGame C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c src/graphics/color.h src/graphics/color.c)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} m)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
