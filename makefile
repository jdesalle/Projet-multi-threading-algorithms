CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread
OBJ=producer_consumer.c philosophe.c my_TnS.c
DEP= my_TnS.h
all:$(OBJ) $(DEP)
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
	$(CC) -o philosophe philosophe.c $(CFLAGS)
	$(CC) -o TnS my_TnS.c my_TnS.h $(CFLAGS)
producer_consumer: producer_consumer.c
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
philosophe: philosophe.c
	$(CC) -o philosophe philosophe.c $(CFLAGS)
TnS: my_TnS.c my_TnS.h 
	$(CC) -o TnS my_TnS. -c $(CFLAGS)