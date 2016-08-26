OBJS = juicyblox_main.o grid.o constants.o block.o
OBJ_NAME = juicyblox
CC = g++
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2 -IC:\Users\ahung89\Projects\juicyblox\src
LIB_PATHS = -LC:\mingw_dev_lib\lib
#iostream doesn't work unless I use gnu++11 to compile c++11
COMPILER_FLAGS = -w -std=gnu++11
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

all : $(OBJS)
	$(CC) $(OBJS) $(LIB_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)

juicyblox_main.o : src/juicyblox_main.cpp
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c src/juicyblox_main.cpp

#src/grid.cpp and src/grid.h are dependencies, so make will rebuild if
#either of them change.
grid.o : src/grid.cpp src/grid.h src/constants.h
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c src/grid.cpp

constants.o : src/constants.cpp src/constants.h
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c src/constants.cpp

block.o : src/block.cpp src/block.h src/block_shape.h src/game_object.h src/point.h
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c src/block.cpp