objFiles = ./build/main.o ./build/attackHand.o ./build/background.o ./build/base.o ./build/blocksHead.o ./build/bullet.o ./build/coffeeCup.o ./build/block.o ./build/dVector2d.o ./build/gun.o ./build/inventory.o ./build/player.o ./build/vector2d.o ./build/pickaxe.o ./build/itemsHead.o ./build/entity.o ./build/entitysHead.o ./build/zombie.o ./build/worldUI.o ./build/text.o ./build/item.o 

CaffeineWorld: $(objFiles)
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o CaffeineWorld $(objFiles)

build/main.o: ./source/main/main.cpp ./source/main/main.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/main.o ./source/main/main.cpp 

build/attackHand.o: ./source/attackHand/attackHand.cpp ./source/attackHand/attackHand.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/attackHand.o ./source/attackHand/attackHand.cpp 

build/background.o: ./source/background/background.cpp ./source/background/background.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/background.o ./source/background/background.cpp 

build/base.o: ./source/base/base.cpp ./source/base/base.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/base.o ./source/base/base.cpp 

build/blocksHead.o: ./source/blocksHead/blocksHead.cpp ./source/blocksHead/blocksHead.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/blocksHead.o ./source/blocksHead/blocksHead.cpp 

build/bullet.o: ./source/bullet/bullet.cpp ./source/bullet/bullet.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/bullet.o ./source/bullet/bullet.cpp 

build/coffeeCup.o: ./source/coffeeCup/coffeeCup.cpp ./source/coffeeCup/coffeeCup.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/coffeeCup.o ./source/coffeeCup/coffeeCup.cpp 

build/block.o: ./source/block/block.cpp ./source/block/block.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/block.o ./source/block/block.cpp 

build/dVector2d.o: ./source/dVector2d/dVector2d.cpp ./source/dVector2d/dVector2d.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/dVector2d.o ./source/dVector2d/dVector2d.cpp 

build/gun.o: ./source/gun/gun.cpp ./source/gun/gun.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/gun.o ./source/gun/gun.cpp 

build/inventory.o: ./source/inventory/inventory.cpp ./source/inventory/inventory.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/inventory.o ./source/inventory/inventory.cpp 

build/player.o: ./source/player/player.cpp ./source/player/player.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/player.o ./source/player/player.cpp 

build/vector2d.o: ./source/vector2d/vector2d.cpp ./source/vector2d/vector2d.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/vector2d.o ./source/vector2d/vector2d.cpp 

build/pickaxe.o: ./source/pickaxe/pickaxe.cpp ./source/pickaxe/pickaxe.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/pickaxe.o ./source/pickaxe/pickaxe.cpp 

build/itemsHead.o: ./source/itemsHead/itemsHead.cpp ./source/itemsHead/itemsHead.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/itemsHead.o ./source/itemsHead/itemsHead.cpp 

build/entity.o: ./source/entity/entity.cpp ./source/entity/entity.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/entity.o ./source/entity/entity.cpp 

build/entitysHead.o: ./source/entitysHead/entitysHead.cpp ./source/entitysHead/entitysHead.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/entitysHead.o ./source/entitysHead/entitysHead.cpp 

build/zombie.o: ./source/zombie/zombie.cpp ./source/zombie/zombie.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/zombie.o ./source/zombie/zombie.cpp 

build/worldUI.o: ./source/worldUI/worldUI.cpp ./source/worldUI/worldUI.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/worldUI.o ./source/worldUI/worldUI.cpp 

build/text.o: ./source/text/text.cpp ./source/text/text.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/text.o ./source/text/text.cpp 

build/item.o: ./source/item/item.cpp ./source/item/item.h
	g++ -c -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o ./build/item.o ./source/item/item.cpp 

run:
	./CaffeineWorld

clean:
	rm ./build/*
	rm CaffeineWorld

all:
	rm ./build/*
	rm CaffeineWorld
	g++ -std=c++23 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -o CaffeineWorld ./source/main/main.cpp ./source/attackHand/attackHand.cpp ./source/background/background.cpp ./source/base/base.cpp ./source/blocksHead/blocksHead.cpp ./source/bullet/bullet.cpp ./source/coffeeCup/coffeeCup.cpp ./source/block/block.cpp ./source/dVector2d/dVector2d.cpp ./source/gun/gun.cpp ./source/inventory/inventory.cpp ./source/player/player.cpp ./source/vector2d/vector2d.cpp ./source/pickaxe/pickaxe.cpp ./source/itemsHead/itemsHead.cpp ./source/entity/entity.cpp ./source/entitysHead/entitysHead.cpp ./source/zombie/zombie.cpp ./source/worldUI/worldUI.cpp ./source/text/text.cpp ./source/item/item.cpp