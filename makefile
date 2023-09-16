files = ./source/main.cpp ./source/vector2d/vector2d.cpp ./source/base/base.cpp ./source/box/box.cpp ./source/background/background.cpp ./source/player/player.cpp
flags = -lSDL2_image

all:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)

launch:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)
	./main

build:
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)