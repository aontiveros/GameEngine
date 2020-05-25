cmake_minimum_required(VERSION 3.15)
project(Chapter2)

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
add_executable(Chapter2 main.cpp
        src/Game.cpp
        header/Game.h
        src/actor/Actor.cpp
        header/actor/Actor.h
        src/component/Component.cpp
        header/component/Component.h
        src/component/SpriteComponent.cpp
        header/component/SpriteComponent.h
        src/Math.cpp header/Math.h
        src/component/AnimSpriteComponent.cpp
        header/component/AnimSpriteComponent.h
        src/component/BGSpriteComponent.cpp
        header/component/BGSpriteComponent.h
        src/actor/Ship.cpp header/actor/Ship.h
        src/component/TileMapComponent.cpp
        header/component/TileMapComponent.h
        src/component/MoveComponent.cpp
        header/component/MoveComponent.h
        src/actor/Asteroid.cpp
        header/actor/Asteroid.h
        src/Random.cpp
        header/Random.h
        src/component/CircleComponent.cpp
        header/component/CircleComponent.h
        src/component/AIComponent.cpp
        header/component/AIComponent.h
        src/state/AIState.cpp
        header/state/AIState.h
        src/state/AIPatrol.cpp
        header/state/AIPatrol.h src/graphics/VertexArray.cpp header/graphics/VertexArray.h src/graphics/Shader.cpp header/graphics/Shader.h src/graphics/Texture.cpp header/graphics/Texture.h src/graphics/Mesh.cpp header/graphics/Mesh.h src/graphics/Renderer.cpp header/graphics/Renderer.h src/component/MeshComponent.cpp header/component/MeshComponent.h src/actor/PlaneActor.cpp header/actor/PlaneActor.h src/actor/CameraActor.cpp header/actor/CameraActor.h)
