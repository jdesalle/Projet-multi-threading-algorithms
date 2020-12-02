CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread
OBJ=producer_consumer.c philosophe.c reader_writer.c
PERSO=my_TnS.c my_TnTnS.c my_semaphore.c  producer_consumer_sem.c philosophe_spin.c reader_writer_sem.c
DEP=my_TnS.h my_TnTnS.h my_semaphore.h
DEST=producer_consumer philosophe reader_writer
DESTPERSO=producer_consumer_sem philosophe_spin reader_writer_sem
all:$(OBJ) $(DEP) $(PERSO)
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
	$(CC) -o philosophe philosophe.c $(CFLAGS)
	$(CC) -o reader_writer reader_writer.c $(CFLAGS)
	$(CC) -o producer_consumer_sem  producer_consumer_sem.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h $(CFLAGS)
	$(CC) -o reader_writer_sem reader_writer_sem.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h $(CFLAGS)
	$(CC) -o philosophe_spin philosophe_spin.c my_TnTnS.c my_TnTnS.h $(CFLAGS)
producer_consumer: producer_consumer.c
	$(CC) -o producer_consumer producer_consumer.c $(CFLAGS)
philosophe: philosophe.c
	$(CC) -o philosophe philosophe.c $(CFLAGS)
reader_writer:reader_writer.c
	$(CC) -o reader_writer reader_writer.c $(CFLAGS)
producer_consumer_sem:producer_consumer.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h
	$(CC) -o producer_consumer_sem  producer_consumer_sem.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h $(CFLAGS)
reader_writer_sem:reader_writer_sem.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h
	$(CC) -o reader_writer_sem reader_writer_sem.c my_semaphore.c my_TnTnS.c  my_sempahore.h my_TnTnS.h $(CFLAGS)
philosophe_spin: philosphe_spin.c my_TnTnS.c my_TnTnS.h
	$(CC) -o philosophe_spin philosophe_spin.c my_TnTnS.c my_TnTnS.h $(CFLAGS)

clean:$(DEST) $(DESTPERSO)
	rm -f $(DEST) $(DESTPERSO)
test:
