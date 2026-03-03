cmake_minimum_required(VERSION 3.28)

project(gbemu)

# add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME})
set(CMAKE_BUILD_TYPE Debug)
target_sources(${PROJECT_NAME} PRIVATE main.c 
                ${CMAKE_CURRENT_SOURCE_DIR}/log.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/bus.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/cart.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/emu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/instructions.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/interrupts.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ppu.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ram.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/rom.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/joypad.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/apu.c)

target_include_directories(${PROJECT_NAME} PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc
                            ${CMAKE_CURRENT_SOURCE_DIR})

# Link SDL to our executable. This also makes its include directory available to us. 
#target_link_libraries(${PROJECT_NAME} PUBLIC 
#    SDL3::SDL3              # If using satelite libraries, SDL must be the last item in the list. 
#)