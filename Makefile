all:
	g++ -std=c++17 -Wall -Werror -g -DMEMTRACE -Isrc/include -Lsrc/lib -o main main.cpp game_end.cpp start.cpp snake.cpp food.cpp memtrace.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_gfx