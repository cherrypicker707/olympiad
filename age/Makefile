COMPILER = clang++
FLAGS = -g
SOURCE_FILES = $(wildcard source/*.cpp)
BINARY_FILES = $(patsubst source/%.cpp, binary/%, $(SOURCE_FILES))

all: $(BINARY_FILES)

binary/%: source/%.cpp
	$(COMPILER) $(FLAGS) -o $@ $^
