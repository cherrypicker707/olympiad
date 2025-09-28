SRC_FILES=$(wildcard src/*.cpp)
BIN_FILES=$(patsubst src/%.cpp, bin/%, $(SRC_FILES))

all: $(BIN_FILES)

bin/%: src/%.cpp
	clang++ -g -fdiagnostics-color=always -o $@ $^
