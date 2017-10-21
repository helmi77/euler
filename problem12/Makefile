CC=gcc
CFLAGS=-std=gnu11

all: euler

euler: euler12.c
	$(CC) $(CFLAGS) -o $@ $< -lm

clean:
	rm -f euler

.PHONY: all clean
