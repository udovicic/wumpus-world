SRCS = main.c world_generator.c
OBJS = main.o world_generator.o
TRGT = wumpus

CC = gcc
CFLAGS = -g -pedantic -Wall -c $(SRCS)

LFLAGS = -o $(TRGT)

$(TRGT): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

clean mrproper:
	rm $(OBJS) $(TRGT)
