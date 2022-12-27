CC = gcc
CFLAGS = -I
DEPS = types.h
OBJ = main.o functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pgnstats: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
