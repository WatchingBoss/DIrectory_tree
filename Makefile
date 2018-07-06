CC = gcc
CFLAGS = -g -Wall

OBJ = tree.o
OUT = tree

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OUT) $(OBJ)
