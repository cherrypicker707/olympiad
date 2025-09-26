SRC_FILES=$(wildcard src/*.cpp)
BIN_FILES=$(patsubst src/%.cpp, bin/%, $(SRC_FILES))

all: $(BIN_FILES)

bin/%: src/%.cpp
	clang++ -o $@ -g -fdiagnostics-color=always $^
