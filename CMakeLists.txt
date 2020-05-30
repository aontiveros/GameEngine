cmake_minimum_required(VERSION 3.15)
project(GameEngine)

set(CMAKE_CXX_STANDARD 14)
INCLUDE(FindPkgConfig)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    link_libraries(${SDL2_LIBRARIES})
    link_libraries(${SDL2_image_LIBRARIES})
endif()

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
INCLUDE_DIRECTORIES( ${SDL2IMAGE_INCLUDE_DIRS})
link_libraries(${SDL2IMAGE_LIBRARIES})

find_package(RapidJSON REQUIRED)
if(RapidJSON_FOUND)
    include_directories(${RapidJSON_INCLUDE_DIRS})
    link_libraries(${RapidJSON_LIBRARIES})
endif()

#find_package(SDL2_image REQUIRED)
#if (SDL2_image_FOUND)
#    include_directories(${SDL2_image_INCLUDE_DIRS})
#    link_libraries(${SDL2_imageL_LIBRARIES})
#endif()

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB files "Shaders/*")
foreach(file ${files})
    get_filename_component(file ${file} NAME)
    message(${file})
    configure_file(Shaders/${file} ${CMAKE_BINARY_DIR}/Shaders/${file})
endforeach()
link_libraries(/usr/lib/libSOIL.so)

#Math library
add_library(math src/Math.cpp include/Math.h src/Random.cpp include/Random.h)
target_include_directories(math PRIVATE include)


# Graphics library
file(GLOB graphics_source src/graphics/*)
file(GLOB graphics_include include/graphics/*)
add_library(render ${graphics_source} ${graphics_include})
target_include_directories(render PRIVATE include)

# Component/Actor Library
file(GLOB game_source src/Game.cpp src/component/* src/actor/* src/state/*)
add_library(component ${game_source})
target_link_libraries(component math render)
target_include_directories(component PRIVATE include)

# Game executable
add_executable(GameEngine src/main.cpp)
target_include_directories(GameEngine PRIVATE include)
target_link_libraries(GameEngine render math component)

