SRCS = main.c world_generator.c game.c graphics.c
HEADS = main.h world_generator.h game.h graphics.h
OBJS = main.o world_generator.o game.o graphics.o
TRGT = wumpus

CC = gcc
CFLAGS = -g -pedantic -Wall -c $(SRCS) `sdl-config --cflags`
LFLAGS = -o $(TRGT) `sdl-config --libs` -lSDL_image -lSDL_ttf

$(TRGT): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS)

$(OBJS): $(SRCS) $(HEADS)
	$(CC) $(CFLAGS) $(SRCS)

clean mrproper:
	rm $(OBJS) $(TRGT)
