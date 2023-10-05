#!/bin/python3

# each group is a folder, which has two files with the same name as the folder but one is .cpp and one is .h
groups = ("attackHand", "background", "base", "blocksHead",
    "bullet", "coffeeCup", "block", "dVector2d",
    "gun", "inventory", "player", "vector2d")

# the compiler flags. Seperated by a space
flags = "-std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf"

objFiles = []
fileGroups = []

for group in groups:
    objFiles.append(group + ".o")
    fileGroups.append({"cpp": f"./source/{group}/{group}.cpp", "header": f"./source/{group}/{group}.h"})

writeMakefileStr = "objFiles = "
for item in objFiles:
    writeMakefileStr += f"./build/{item} "
writeMakefileStr += "./build/main.o "

writeMakefileStr += "\n\r\n"

writeMakefileStr += "CaffeineWorld: $(objFiles)\n\t"
writeMakefileStr += f"g++ {flags} -o CaffeineWorld $(objFiles)\n\r\n"

writeMakefileStr += f"build/main.o: ./source/main.cpp ./source/main.h\n\t"
writeMakefileStr += f"g++ -c {flags} -o ./build/main.o ./source/main.cpp\n\r\n"

for i in range(len(groups)):
    writeMakefileStr += f"build/{objFiles[i]}: {fileGroups[i]['cpp']} {fileGroups[i]['header']}\n\t"
    writeMakefileStr += f"g++ -c {flags} -o ./build/{objFiles[i]} {fileGroups[i]['cpp']} \n\r\n"

writeMakefileStr += f"run:\n\t./CaffeineWorld\n\r\nclean:\n\trm ./build/*\n\trm CaffeineWorld\n"

makefile = open("makefile", "w")
makefile.write(writeMakefileStr)
makefile.close()