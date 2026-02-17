cmake_minimum_required(VERSION 4.0.0)
set(PROJECT_NAME Pong)
project(${PROJECT_NAME} VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)

set(SRC_FILES 
    ./src/main.cpp
    ./src/App.hpp
    ./src/GameClasses/Base/GameObject.hpp
    ./src/GameClasses/Base/InputManager.hpp
    ./src/GameClasses/Base/PhysicsCheck.hpp
    ./src/GameClasses/MainScene.hpp
    ./src/GameClasses/Racket.hpp
    ./src/GameClasses/Ball.hpp)

find_package(Gorgon REQUIRED)
add_executable(${PROJECT_NAME} ${SRC_FILES})

linkgorgon(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resource/ball.png ${CMAKE_CURRENT_SOURCE_DIR}/Bin/Resource/ball.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resource/racket.png ${CMAKE_CURRENT_SOURCE_DIR}/Bin/Resource/racket.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resource/font.ttf ${CMAKE_CURRENT_SOURCE_DIR}/Bin/Resource/font.ttf COPYONLY)








