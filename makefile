CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread
OBJ=producer_consumer.c philosophe.c my_TnS.c reader_writer.c my_TnTnS.c

DEP= my_TnS.h my_TnTnS.h
all:$(OBJ) $(DEP)
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
	$(CC) -o philosophe philosophe.c $(CFLAGS)
	$(CC) -o TnS my_TnS.c my_TnS.h $(CFLAGS)
	$(CC) -o reader_writer reader_writer.c $(CFLAGS)
	$(CC) -o TnTnS my_TnTnS.c my_TnTnS.h $(CFLAGS)
producer_consumer: producer_consumer.c
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
philosophe: philosophe.c
	$(CC) -o philosophe philosophe.c $(CFLAGS)
TnS: my_TnS.c my_TnS.h 
	$(CC) -o TnS my_TnS.c my_TnS.h $(CFLAGS)
reader_writer:reader_writer.c
	$(CC) -o reader_writer reader_writer.c $(CFLAGS)
TnTnS: my_TnTnS.c  my_TnTnS.h
	$(CC) -o TnTnS my_TnTnS.c my_TnTnS.h $(CFLAGS)

