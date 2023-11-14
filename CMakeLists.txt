cmake_minimum_required(VERSION 3.15)
project(ArrowGame C)

set(CMAKE_C_STANDARD 99)
set(RESOURCES Assets/Arrow.png Assets/font.otf Config/default.icfg)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message("Updating submodules...")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE UPDATE_RES)
    if(NOT UPDATE_RES EQUAL "0")
        message(FATAL_ERROR "Updating failed. Error code: ${UPDATE_RES}")
    endif()
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/SDL/CMakeLists.txt)
    message(FATAL_ERROR "Updating SDL failed")
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/SDL_image/CMakeLists.txt)
    message(FATAL_ERROR "Updating SDL_image failed")
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/SDL_ttf/CMakeLists.txt)
    message(FATAL_ERROR "Updating SDL_ttf failed")
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/freetype/CMakeLists.txt)
    message(FATAL_ERROR "Updating SDL_ttf failed")
endif()


add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(freetype)
add_subdirectory(SDL_ttf)

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
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf)
target_link_libraries(${PROJECT_NAME} m)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror)


