CC = gcc
CFLAGS = -g -Wall
DIR = ./include/

DEPS = $(DIR)tree.h $(DIR)common.h
OBJ = tree.o common.o 
OUT = tree

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OUT) $(OBJ)
