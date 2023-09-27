s = ./source/
files = $(s)main.cpp $(s)vector2d/vector2d.cpp $(s)base/base.cpp $(s)box/box.cpp $(s)background/background.cpp $(s)player/player.cpp $(s)inventory/inventory.cpp $(s)gun/gun.cpp $(s)attackHand/attackHand.cpp

flags = -lSDL2_image

CaffeineWorld: $(files)
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)

run:
	./CaffeineWorld

clean:
	rm CaffeineWorld