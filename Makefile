CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread

producer_consumer: producer_consumer.c
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
