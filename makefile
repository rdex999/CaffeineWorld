all:
	g++ -Wall `sdl2-config --cflags --libs` -o main ./source/main.cpp