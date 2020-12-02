CC= gcc
CFLAGS=-I -std=c99  -Wall -Werror -pthread
OBJ=OBJ/producer_consumer.c OBJ/philosophe.c OBJ/reader_writer.c
PERSO=PERSO/my_TnS.c  PERSO/my_TnTnS.c PERSO/my_semaphore.c  PERSO/producer_consumer_sem.c PERSO/philosophe_spin.c PERSO/reader_writer_sem.c
DEP=DEP/my_TnS.h DEP/my_TnTnS.h DEP/my_semaphore.h
DEST=producer_consumer philosophe reader_writer
DESTPERSO=producer_consumer_sem philosophe_spin reader_writer_sem
TEST=test_verrouTnS.c test_verrouTnTnS.c
all:$(OBJ) $(DEP) $(PERSO) $(TEST)
	$(CC) -o producer_consumer OBJ/producer_consumer.c $(CFLAGS)
	$(CC) -o philosophe OBJ/philosophe.c $(CFLAGS)
	$(CC) -o reader_writer OBJ/reader_writer.c $(CFLAGS)
	$(CC) -o producer_consumer_sem  PERSO/producer_consumer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h $(CFLAGS)
	$(CC) -o reader_writer_sem PERSO/reader_writer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h $(CFLAGS)
	$(CC) -o philosophe_spin PERSO/philosophe_spin.c PERSO/my_TnTnS.c DEP/my_TnTnS.h $(CFLAGS)
	$(CC) -o test_verrouTnTnS test_verrouTnTnS.c PERSO/my_TnTnS.c DEP/my_TnTnS.h $(CFLAGS)
	$(CC) -o test_verrouTnS test_verrouTnS.c PERSO/my_TnS.c DEP/my_TnS.h $(CFLAGS)
producer_consumer: OBJ/producer_consumer.c
	$(CC) -o producer_consumer OBJ/producer_consumer.c $(CFLAGS)
philosophe: OBJ/philosophe.c
	$(CC) -o philosophe OBJ/philosophe.c $(CFLAGS)
reader_writer:OBJ/reader_writer.c
	$(CC) -o reader_writer OBJ/reader_writer.c $(CFLAGS)
producer_consumer_sem:PERSO/producer_consumer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h
	$(CC) -o producer_consumer_sem  PERSO/producer_consumer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h $(CFLAGS)
reader_writer_sem:PERSO/reader_writer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h
	$(CC) -o reader_writer_sem PERSO/reader_writer_sem.c PERSO/my_semaphore.c PERSO/my_TnTnS.c  DEP/my_semaphore.h DEP/my_TnTnS.h $(CFLAGS)
philosophe_spin: PERSO/philosphe_spin.c PERSO/my_TnTnS.c DEP/my_TnTnS.h
	$(CC) -o philosophe_spin PERSO/philosophe_spin.c PERSO/my_TnTnS.c DEP/my_TnTnS.h $(CFLAGS)
test_verrouTnS: test_verrouTnS test_verrouTnS.c PERSO/my_TnS.c DEP/my_TnS.h
	$(CC) -o test_verrouTnS test_verrouTnS.c PERSO/my_TnS.c DEP/my_TnS.h $(CFLAGS)
test_verrouTnTnS: test_verrouTnTnS test_verrouTnTnS.c PERSO/my_TnTnS.c DEP/my_TnTnS.h
	$(CC) -o test_verrouTnTnS test_verrouTnTnS.c PERSO/my_TnTnS.c DEP/my_TnTnS.h $(CFLAGS)
clean:$(DEST) $(DESTPERSO)
	rm -f $(DEST) $(DESTPERSO)
test:
	$(CC) -o test_verrouTnTnS test_verrouTnTnS.c PERSO/my_TnTnS.c DEP/my_TnTnS.h $(CFLAGS)
	$(CC) -o test_verrouTnS test_verrouTnS.c PERSO/my_TnS.c DEP/my_TnS.h $(CFLAGS)
	./test_verrouTnS
	./test_verrouTnTnS
