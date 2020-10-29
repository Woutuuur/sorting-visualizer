SRC = src/*.cpp
LIBS = -I ./include
CC = g++
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
BINARY_NAME = sorter
all: $(SRC)
	$(CC) $(LIBS) $(SRC) $(LINKER_FLAGS) -o $(BINARY_NAME)
