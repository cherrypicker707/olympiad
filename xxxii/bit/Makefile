CC=clang++
CFLAGS=-g
SRC_DIR=src
BIN_DIR=bin
SRC_FILES=$(wildcard src/*.cpp)
BIN_FILES=$(patsubst src/%.cpp, bin/%, $(SRC_FILES))

all: $(BIN_FILES)

bin/%: src/%.cpp
	$(CC) -o $@ $(CFLAGS) $^
