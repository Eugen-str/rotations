all: main.c rot.h
	cc main.c -o main -lm -lSDL2
