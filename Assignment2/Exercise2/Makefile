CC = gcc
CFLAGS = -O3 -Wall -Wextra
LDFLAGS = -lm

all: numerical_diff

numerical_diff: numerical_diff.c
	$(CC) $(CFLAGS) -o numerical_diff numerical_diff.c $(LDFLAGS)

clean:
	rm -f numerical_diff numerical_diff.txt
