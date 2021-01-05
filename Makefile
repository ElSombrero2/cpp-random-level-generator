SRC = $(wildcard *.cpp)
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
INCLUDES=include
OUTPUT=bin/debug.exe
CC=g++
LIB_DIR=-Llib

build:
	$(CC) $(SRC) -o $(OUTPUT) -I $(INCLUDES) $(LIB_DIR) $(LIBS)

run:$(OUTPUT)
	$(OUTPUT)