CC=gcc
CFLAGS=-g -Wall
OBJ=copy.o error_functions.o
EXE=csc60cp

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
copy.o: tlpi_hdr.h copy.c
	$(CC) $(CFLAGS) -c copy.c
error_functions.o: error_functions.h tlpi_hdr.h ename.c.inc
	$(CC) $(CFLAGS) -c error_functions.c
clean:
	rm $(OBJ) 
