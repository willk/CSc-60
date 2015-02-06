# Simple Makefile for mystat program
# seven.c error_functions.c get_num.c curr_time.c semun.h
CC=gcc
CFLAGS=-g3 -Wall
OBJ=seven.o error_functions.o curr_time.o get_num.o
EXE=sem_sync

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
seven.o: tlpi_hdr.h semun.h get_num.h curr_time.h seven.c
	$(CC) $(CFLAGS) -c seven.c
error_functions.o: error_functions.h tlpi_hdr.h ename.c.inc error_functions.c
	$(CC) $(CFLAGS) -c error_functions.c
curr_time.o: curr_time.h
	$(CC) $(CFLAGS) -c curr_time.c
get_num.c: get_num.h
	$(CC) $(CFLAGS) -c get_num.c
clean:
	rm $(OBJ)
