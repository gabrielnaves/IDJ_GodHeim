cmake_minimum_required (VERSION 2.6)
project (GodHeim)

add_definitions(-std=c++11)

find_package(sdl2 REQUIRED)

include_directories(
  include/
  ${SDL2_INCLUDE_DIRS}
)

add_executable(GodHeim
    src/Main.cpp
    src/engine/cpp/BlockTileSet.cpp
    src/engine/cpp/Camera.cpp
    src/engine/cpp/Game.cpp
    src/engine/cpp/InputManager.cpp
    src/engine/cpp/LineSegment.cpp
    src/engine/cpp/MovementMap.cpp
    src/engine/cpp/MultiTileSet.cpp
    src/engine/cpp/Music
    src/engine/cpp/Point.cpp
    src/engine/cpp/Rect.cpp
    src/engine/cpp/Resource.cpp
    src/engine/cpp/Sound.cpp
    src/engine/cpp/Sprite.cpp
    src/engine/cpp/State.cpp
    src/engine/cpp/StillAnimation.cpp
    src/engine/cpp/Text.cpp
    src/engine/cpp/TileMap.cpp
    src/engine/cpp/TileSet.cpp
    src/engine/cpp/Timer.cpp
    src/specificCode/characters/cpp/Barrier.cpp
    src/specificCode/characters/cpp/Bullet.cpp
    src/specificCode/characters/cpp/ChainedDragon.cpp
    src/specificCode/characters/cpp/Character.cpp
    src/specificCode/characters/cpp/ClimbMov.cpp
    src/specificCode/characters/cpp/EagleMov.cpp
    src/specificCode/characters/cpp/GateMov.cpp
    src/specificCode/characters/cpp/Goat.cpp
    src/specificCode/characters/cpp/HoldingWolf.cpp
    src/specificCode/characters/cpp/HpBar.cpp
    src/specificCode/characters/cpp/Loki.cpp
    src/specificCode/characters/cpp/MovementState.cpp
    src/specificCode/characters/cpp/RegularMov.cpp
    src/specificCode/characters/cpp/Skeleton.cpp
    src/specificCode/characters/cpp/Thor.cpp
    src/specificCode/characters/cpp/Wolf.cpp
    src/specificCode/gameStates/cpp/Credits.cpp
    src/specificCode/gameStates/cpp/EndState.cpp
    src/specificCode/gameStates/cpp/Level1State.cpp
    src/specificCode/gameStates/cpp/Level2State.cpp
    src/specificCode/gameStates/cpp/OptionsState.cpp
    src/specificCode/gameStates/cpp/StateData.cpp
    src/specificCode/gameStates/cpp/TitleState.cpp
    src/specificCode/items/cpp/Item.cpp
    src/specificCode/items/cpp/ItemFlags.cpp
    src/specificCode/objects/cpp/ArrowButton.cpp
    src/specificCode/objects/cpp/Bridge.cpp
    src/specificCode/objects/cpp/BrokenHouseBack.cpp
    src/specificCode/objects/cpp/BrokenHouseFront.cpp
    src/specificCode/objects/cpp/Cursor.cpp
    src/specificCode/objects/cpp/FloatingBlock.cpp
    src/specificCode/objects/cpp/Gate.cpp
    src/specificCode/objects/cpp/Geyser.cpp
    src/specificCode/objects/cpp/LavaCircle.cpp
    src/specificCode/objects/cpp/Lava.cpp
    src/specificCode/objects/cpp/MenuBox.cpp
    src/specificCode/objects/cpp/Meteor.cpp
    src/specificCode/objects/cpp/OptionBox.cpp
    src/specificCode/objects/cpp/PlantBarrier.cpp
    src/specificCode/objects/cpp/Plants.cpp
    src/specificCode/objects/cpp/Portal.cpp
    src/specificCode/objects/cpp/Rock.cpp
    src/specificCode/objects/cpp/Rope.cpp
    src/specificCode/objects/cpp/Spikes.cpp
    src/specificCode/objects/cpp/Stairs.cpp
    src/specificCode/objects/cpp/StoneBlock.cpp
    src/specificCode/objects/cpp/Switch.cpp
)
target_link_libraries(GodHeim SDL2 SDL2_image SDL2_mixer SDL2_ttf)
