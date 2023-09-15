files = ./source/main.cpp ./source/vector2d/vector2d.cpp ./source/base/base.cpp ./source/box/box.cpp ./source/background/background.cpp
flags = -lSDL2_image

all:
	g++ -Wall `sdl2-config --cflags --libs` $(flags) -o main $(files)

launch:
	g++ -Wall `sdl2-config --cflags --libs` $(flags) -o main $(files)
	./main

build:
	g++ -Wall `sdl2-config --cflags --libs` $(flags) -o main $(files)