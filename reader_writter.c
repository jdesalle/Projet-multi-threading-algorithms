/*
 *Implementation of the reader/writter problem realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t mreaders;//protect readers and nread
pthread_mutex_t mwriters;//protect writers and nwrite
pthread_mutex_t x;//check only one reader use sem_wait at a time
sem_t swrite;//block writers
sem_t sread;//block readers
int readers=0;//number of reader currently reading
int writers=0;//number of writers waiting
int nread=0;//number of reading already done (shoudl go to 2560)
int nwrite=0;//number of writing alreadydone.(should go to 640)

void reader(void *args){
	while(nread<2560){
		
	}
}
void writers(void *args){
	while(nwrite<640){
		pthread_mutex_lock(&mwriters);
			writers++; //a new writer has arrived
			if (writers==1){// first writer to arrive
				sem_wait(&sread);
			}
		pthread_mutex_unlock(&mwriters);
		sem_wait(&swrite);
			while(rand() > RAND_MAX/10000);//simulate action on db
		sem_post(&swrite);
		pthread_mutex_lock(&mwriters);
			nwrite++://one more read has been done
			writers --;//the writer exute from the db
			if (writers==0){//last writer
				sem_post(&sread);
			}
		pthread_mutex_unlock(&mwriters);
	}
}
int maint (int argc, char* argv[]){
	return 0
}