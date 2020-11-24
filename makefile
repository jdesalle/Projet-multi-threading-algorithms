CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread
OBJ=producer_consumer.c philosophe.c
all:$(OBJ)
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
	$(CC) -o philosophe philosophe.c $(CFLAGS)

producer_consumer: producer_consumer.c
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
philosophe: philosophe.c
	$(CC) -o philosophe philosophe.c $(CFLAGS)
