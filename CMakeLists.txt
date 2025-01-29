
cmake_minimum_required(VERSION 3.5.0)
project(Pong VERSION 0.1.0 LANGUAGES C)

option(Pong_VENDORED "Use vendored libraries" ON)
option(SDLTTF_VENDORED "Use vendored SDL_ttf" ${Pong_VENDORED})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

if(Pong_VENDORED)
    add_subdirectory(Vendor/SDL EXCLUDE_FROM_ALL)
    add_subdirectory(Vendor/SDL_ttf EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

    find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3main)
endif()

add_subdirectory(Vendor/Vector)

add_library(PongLib STATIC ./src/PongMain.c ./src/Renderer.c ./src/Texture.c ./src/Fonts.c ./src/Events.c ./src/Timestep.c ./src/Paddle.c ./src/Player.c ./src/Ball.c)

target_include_directories(PongLib PUBLIC Vendor/Vector)

if(TARGET SDL3::SDL3main)
    target_link_libraries(PongLib PUBLIC SDL3::SDL3main)
endif()
target_link_libraries(PongLib PUBLIC SDL3::SDL3 SDL3_ttf::SDL3_ttf)
target_link_libraries(PongLib PUBLIC Vector)

add_executable(PongGame ./game/main.c)
target_include_directories(PongGame PRIVATE src/)
target_link_libraries(PongGame PongLib)

add_custom_command(
        TARGET PongGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/joystixmonospace.ttf
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/joystixmonospace.ttf)