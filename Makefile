CC= g++
CFLAGS = -Wall -std=c++11
LIBS = -lOpenGL -lglut -lGLU

all: bin/circle1 bin/circle2 bin/circle3
	@echo Done

bin/%: build/%.o
	$(CC) -o $@ $(CFLAGS) $(LIBS) $^

build/%.o: src/%.cpp
	$(CC) -o $@ $(CFLAGS) $(LIBS) -c $<
