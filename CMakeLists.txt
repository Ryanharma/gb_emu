cmake_minimum_required(VERSION 3.28)

project(gbemu)

add_executable(${PROJECT_NAME})
set(CMAKE_BUILD_TYPE Debug)
target_sources(${PROJECT_NAME} PRIVATE main.c 
                ${CMAKE_CURRENT_SOURCE_DIR}/log.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/bus.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/cart.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/emu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/instructions.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ppu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ram.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/vram.c)

target_include_directories(${PROJECT_NAME} PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc
                            ${CMAKE_CURRENT_SOURCE_DIR})