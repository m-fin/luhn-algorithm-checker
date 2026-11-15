CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

.PHONY: all test clean

all: luhn

luhn: luhn.c
	$(CC) $(CFLAGS) -o luhn luhn.c

test: luhn
	sh test.sh

clean:
	rm -f luhn *.o
