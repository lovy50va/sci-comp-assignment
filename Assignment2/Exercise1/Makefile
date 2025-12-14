CC = gcc
CFLAGS = -O3 -Wall

all: axpy_test

axpy_test: main.o axpy.o
	$(CC) $(CFLAGS) -o axpy_test main.o axpy.o

main.o: main.c axpy.h
	$(CC) $(CFLAGS) -c main.c

axpy.o: axpy.c axpy.h
	$(CC) $(CFLAGS) -c axpy.c

measurements:
	$(CC) $(CFLAGS) -DMEASUREMENTS main.c axpy.c -o axpy_measure

clean:
	rm -f *.o axpy_test axpy_measure measurements.csv
