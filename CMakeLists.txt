cmake_minimum_required(VERSION 3.15)
project(ArrowGame C)

set(CMAKE_C_STANDARD 99)
set(RESOURCES Assets/Arrow.png Assets/font.otf Config/default.icfg)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

option(SDL_VENDORED "Use vendored libraries" OFF)

if(SDL_VENDORED)
    set(SDL2_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/SDL2/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/SDL2_image/include")
    set(SDL2_TTF_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/SDL2_ttf/include")
    set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib")
    set(SDL2_IMAGE_LIBRARIES "${CMAKE_SOURCE_DIR}/SDL2_image/lib/x64/SDL2_image.lib")
    set(SDL2_TTF_LIBRARIES "${CMAKE_SOURCE_DIR}/SDL2_ttf/lib/x64/SDL2_ttf.lib")
    add_compile_definitions(VENDORED)
else()
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif()

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
if(TARGET SDL2::SDL2main)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
endif()
if(SDL_VENDORED)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
endif()
target_link_libraries(${PROJECT_NAME} m)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror)


