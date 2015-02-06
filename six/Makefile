CC=gcc
CFLAGS=-Wall -std=c99 -D_POSIX_C_SOURCE=200112L
OBJ=msh.o
EXE=msh

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
msh.o: msh.c
	$(CC) $(CFLAGS) -c msh.c
clean:
	rm $(OBJ)

