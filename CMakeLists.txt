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


#find_package(SDL2_image REQUIRED)
#if (SDL2_image_FOUND)
#    include_directories(${SDL2_imageL_INCLUDE_DIRS})
#endif()
#${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES}


file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Shaders DESTINATION ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}/Shaders/")


add_executable(Chapter2 main.cpp
        src/Game.cpp
        header/Game.h
        src/Actor.cpp
        header/Actor.h
        src/component/Component.cpp
        header/component/Component.h
        src/component/SpriteComponent.cpp
        header/component/SpriteComponent.h
        src/Math.cpp header/Math.h
        src/component/AnimSpriteComponent.cpp
        header/component/AnimSpriteComponent.h
        src/component/BGSpriteComponent.cpp
        header/component/BGSpriteComponent.h
        src/Ship.cpp header/Ship.h
        src/component/TileMapComponent.cpp
        header/component/TileMapComponent.h
        src/component/MoveComponent.cpp
        header/component/MoveComponent.h
        src/Asteroid.cpp
        header/Asteroid.h
        src/Random.cpp
        header/Random.h
        src/component/CircleComponent.cpp
        header/component/CircleComponent.h
        src/component/AIComponent.cpp
        header/component/AIComponent.h
        src/state/AIState.cpp
        header/state/AIState.h
        src/state/AIPatrol.cpp
        header/state/AIPatrol.h src/graphics/VertexArray.cpp header/graphics/VertexArray.h src/graphics/Shader.cpp header/graphics/Shader.h)
