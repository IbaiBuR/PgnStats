CC = gcc
CFLAGS = -I
DEPS = include.h
OBJ = functions.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pgnstats: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
