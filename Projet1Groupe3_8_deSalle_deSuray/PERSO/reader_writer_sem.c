/*
 *Implementation of the reader/writter problem realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "../DEP/my_semaphore.h"
#include "../DEP/my_TnTnS.h"

TnTnS_t mreaders;//protect readers and nread
TnTnS_t mwriters;//protect writers and nwrite
TnTnS_t x;//allow priority for writers
my_sem_t swrite;//block writers
my_sem_t sread;//block readers

int readers=0;//number of reader currently reading
int writers=0;//number of writers waiting
int nread=0;//number of reading already done (should go to argreader)
int nwrite=0;//number of writing already done.(should go to argwriter)
int argreader=2560;
int argwriter=640;

void *reader(void *args){
	//puts("called reader");
	while(nread<argreader){
		lock(&x);
			my_sem_wait(&sread);//new writer waiting
			lock(&mreaders);
				readers++;//a new reader has arrived
				if (readers==1){//first reader
					my_sem_wait(&swrite);
//puts("entered reader SC1");
				}
			unlock(&mreaders);
			my_sem_post(&sread);//allow nex reader to proceed
		unlock(&x);
		while(rand() > RAND_MAX/10000);//simulate action on db
		//puts("read");
		lock(&mreaders);
			nread++;
			readers--;
			if (readers==0){//last reader
				my_sem_post(&swrite);
			}
		unlock(&mreaders);
	}
	pthread_exit(NULL);
}
void *writer(void *args){
	//puts("called writer");
	while(nwrite<argwriter){
		lock(&mwriters);
			writers++; //a new writer has arrived
			if (writers==1){// first writer to arrive
				my_sem_wait(&sread);
			}
		unlock(&mwriters);
		my_sem_wait(&swrite);//only one writer on the db at a time
			while(rand() > RAND_MAX/10000);//simulate action on db
			//puts("write");
		my_sem_post(&swrite);
		lock(&mwriters);
			nwrite++;//one more read has been done
			writers --;//the writer exute from the db
			if (writers==0){//last writer
				my_sem_post(&sread);
			}
		unlock(&mwriters);
	}
	pthread_exit(NULL);
}
int main (int argc, char* argv[]){
	char ch;
	int nthread=3;
	int nthread_readers;
	int nthread_writers;
	while ((ch=getopt(argc, argv, "r:w:t:")) !=  EOF){
		switch(ch){
			case 't':
				nthread=atoi(optarg);
				break;
			case 'r':
				argreader=atoi(optarg);
				break;
			case 'w':
				argwriter=atoi(optarg);
				break;
			default:
				fprintf(stderr, "invalid argument");
		}
	}
	nthread_writers=nthread/2;
	nthread_readers=(nthread%2==0) ? nthread/2 : (nthread/2)+1;
	//printf("%d %d %d\n", nthread, nthread_readers,nthread_writers);
	init(&mreaders);
	init(&mwriters);
	init(&x);
	my_sem_init (&swrite,1);
	my_sem_init (&sread,1);

	pthread_t thread_readers[nthread_readers];
	pthread_t thread_writers[nthread_writers];
	int err;
	//puts("init");
	for (int i=0; i<nthread_readers;i++){//create readers threads
		err=pthread_create(&(thread_readers[i]),NULL,reader,NULL);
		//printf ("tried pthread %d create read\n",i);
		if(err!=0){
			fprintf(stderr,"Error creating thread reader %d\n", i);
		}
	}
	for (int i=0; i<nthread_writers;i++){//create writers threads
		err=pthread_create(&(thread_writers[i]),NULL,writer,NULL);
		//printf ("tried pthread %d create write\n",i);
		if(err!=0){
			fprintf(stderr,"Error creating thread writer %d\n", i);
		}
	}
	for (int i=0; i<nthread_readers;i++){
		pthread_join(thread_readers[i],NULL);
	}
	for (int i=0; i<nthread_writers;i++){
		pthread_join(thread_writers[i],NULL);
	}
	//TO DO  destroy mutexes and semaphores
	return 0;
}
