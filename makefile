s = ./source/
files = \
	$(s)main.cpp $(s)vector2d/vector2d.cpp $(s)base/base.cpp \
	$(s)background/background.cpp $(s)player/player.cpp \
	$(s)inventory/inventory.cpp $(s)gun/gun.cpp $(s)attackHand/attackHand.cpp \
	$(s)bullet/bullet.cpp $(s)dVector2d/dVector2d.cpp $(s)coffeeCup/coffeeCup.cpp \
	$(s)dirtBlock/dirtBlock.cpp $(s)blocksHead/blocksHead.cpp

flags = -lSDL2_image -lSDL2_ttf

CaffeineWorld: $(files)
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` $(flags) -o CaffeineWorld $(files)

run:
	./CaffeineWorld

clean:
	rm CaffeineWorld