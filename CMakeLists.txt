cmake_minimum_required(VERSION 3.15)
project(ArrowGame C)

set(CMAKE_C_STANDARD 99)
set(RESOURCES Assets/Arrow.png Assets/font.otf Config/default.icfg)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

FOREACH(RES ${RESOURCES})
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${RES}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${RES}
            ${CMAKE_CURRENT_BINARY_DIR}/${RES}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${RES}
  )
ENDFOREACH()


list(TRANSFORM RESOURCES PREPEND ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(${PROJECT_NAME} ${RESOURCES} main.c debugmalloc.h)
add_library(Game SHARED debugmalloc.h)
add_subdirectory(src)

add_subdirectory(Menus)

target_link_libraries(${PROJECT_NAME} Game)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} m)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror)


