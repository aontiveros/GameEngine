cmake_minimum_required(VERSION 3.15)
project(Chapter2)

set(CMAKE_CXX_STANDARD 14)
include_directories(${SDL2_INCLUDE_DIRS})
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2>=2.0.0)
PKG_SEARCH_MODULE(SDL2_image REQUIRED SDL2_image>=2.0.0)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Chapter2 main.cpp src/Game.cpp header/Game.h src/Actor.cpp header/Actor.h src/component/Component.cpp header/component/Component.h src/component/SpriteComponent.cpp header/component/SpriteComponent.h src/Math.cpp header/Math.h src/component/AnimSpriteComponent.cpp header/component/AnimSpriteComponent.h src/component/BGSpriteComponent.cpp header/component/BGSpriteComponent.h src/Ship.cpp header/Ship.h src/component/TileMapComponent.cpp header/component/TileMapComponent.h src/component/MoveComponent.cpp header/component/MoveComponent.h src/Asteroid.cpp header/Asteroid.h src/Random.cpp header/Random.h src/component/CircleComponent.cpp header/component/CircleComponent.h src/component/AIComponent.cpp header/component/AIComponent.h src/state/AIState.cpp header/state/AIState.h src/state/AIPatrol.cpp header/state/AIPatrol.h)
target_link_libraries(Chapter2 ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES})