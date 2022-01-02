CC = g++
FLAGS= -Wall -Iinclude
SRCS := $(wildcard src/*.cpp *.cpp)
OBJS := $(SRCS:src/%.cpp=build/%.o)
NAME=main

all: build/$(NAME)

debug: FLAGS:= -g -O0 $(FLAGS)
debug: all

release: FLAGS:= -O3 $(FLAGS)
release: all

clean:
	rm -rf build/*

build/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $^

build/$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

