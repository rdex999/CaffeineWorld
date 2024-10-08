#!/bin/python3

# each group is a folder, which has two files with the same name as the folder but one is .cpp and one is .h
groups = ("attackHand", "background", "base", "blocksHead",
    "bullet", "coffeeCup", "block", "dVector2d",
    "gun", "inventory", "player", "vector2d", "pickaxe", "itemsHead",
    "entity", "entitysHead", "zombie", "worldUI", "text", "item",
    "tree", "treesHead")

libs = ("SDL2", "SDL2main", "SDL2_ttf", "SDL2_image")

cmakeStr = """
# 
# GENERATED BY 'generateCmake.py'
# DO NOT EDIT
# 

cmake_minimum_required(VERSION 3.27.7)
project(CaffeineWorld VERSION 0.1.0 LANGUAGES C CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CTest)
enable_testing()
include(CPack)

add_executable(CaffeineWorld source/main/main.cpp)

link_libraries(
"""

for lib in libs:
    cmakeStr += f"\t{lib}\n"

cmakeStr += ")\n\n"

for group in groups:
    cmakeStr += f"add_subdirectory(source/{group})\n"

cmakeStr += "\n"

cmakeStr += "target_link_libraries(CaffeineWorld\n"
for group in groups:
    cmakeStr += f"\t{group}\n"

cmakeStr += ")"

cmakeFile = open("CMakeLists.txt", "w")
cmakeFile.write(cmakeStr)
cmakeFile.close()