s = ./source/
files = $(s)main.cpp $(s)vector2d/vector2d.cpp $(s)base/base.cpp $(s)box/box.cpp $(s)background/background.cpp $(s)player/player.cpp
flags = -lSDL2_image

all:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)

launch:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)
	./main

build:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)