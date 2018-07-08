CC = gcc
CFLAGS = -g -Wall

DEPS = tree.h common.h
OBJ = tree.o common.o 
OUT = tree

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OUT) $(OBJ)
