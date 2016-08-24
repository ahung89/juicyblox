OBJS = juicyblox_main.o
OBJ_NAME = juicyblox
CC = g++
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2 -IC:\Users\ahung89\Projects\juicyblox\src
LIB_PATHS = -LC:\mingw_dev_lib\lib
COMPILER_FLAGS = -w -std=gnu++11
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

all : $(OBJS)
	$(CC) $(OBJS) $(LIB_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)

juicyblox_main.o : src/juicyblox_main.cpp src/juicyblox_main.h
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c src/juicyblox_main.cpp