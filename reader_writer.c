/*
 *Implementation of the reader/writter problem realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
pthread_mutex_t mreaders;//protect readers and nread
pthread_mutex_t mwriters;//protect writers and nwrite
pthread_mutex_t x;//allow priority for writers
sem_t swrite;//block writers
sem_t sread;//block readers
int readers=0;//number of reader currently reading
int writers=0;//number of writers waiting
int nread=0;//number of reading already done (should go to argreader)
int nwrite=0;//number of writing already done.(should go to argwriter)
int argreader=2560;
int argwriter=640;
void *reader(void *args){
	while(nread<2560){
		pthread_mutex_lock(&x);
			sem_wait(&sread);//new writer waiting
			pthread_mutex_lock(&mreaders);
				readers++;//a new reader has arrived
				if (readers==1){//first reader
					sem_wait(&swrite);
				}
			pthread_mutex_unlock(&mreaders);
			sem_post(&sread);//allow nex reader to proceed
		pthread_mutex_unlock(&x);
		while(rand() > RAND_MAX/10000);//simulate action on db
		pthread_mutex_lock(&mreaders);
			nread++;
			readers--;
			if (readers==0){//last reader
				sem_post(&swrite);
			}
		pthread_mutex_unlock(&mreaders);
	}
	pthread_exit(NULL);
}
void *writer(void *args){
	while(nwrite<640){
		pthread_mutex_lock(&mwriters);
			writers++; //a new writer has arrived
			if (writers==1){// first writer to arrive
				sem_wait(&sread);
			}
		pthread_mutex_unlock(&mwriters);
		sem_wait(&swrite);//only one writer on the db at a time
			while(rand() > RAND_MAX/10000);//simulate action on db
		sem_post(&swrite);
		pthread_mutex_lock(&mwriters);
			nwrite++;//one more read has been done
			writers --;//the writer exute from the db
			if (writers==0){//last writer
				sem_post(&sread);
			}
		pthread_mutex_unlock(&mwriters);
	}
	pthread_exit(NULL);
}
int main (int argc, char* argv[]){
	char ch;
	int nthread_readers=1;
	int nthread_writers=1;
	while ((ch=getopt(argc, argv, "rt:wr:r:w:")) !=  EOF){
		switch(ch){
			case 'r':
				nthread_readers=atoi(optarg);
				break;
			case 'w':
				nthread_writers=atoi(optarg);
				break;
			case 'l':
				argreader=atoi(optarg);
				break;
			case 'e':
				argwriter=atoi(optarg);
				break;
			default:
				fprintf(stderr, "invalid argument");
		}
	}
	pthread_mutex_init(&mreaders,NULL);
	pthread_mutex_init(&mwriters,NULL);
	pthread_mutex_init (&x,NULL);
	sem_init (&swrite,0,0);
	sem_init (&sread,0,0);

	pthread_t thread_readers[nthread_readers];
	pthread_t thread_writers[nthread_writers];
	int err;
	for (int i=0; i<argreader;i++){//create readers threads
		err=pthread_create(&(thread_readers[i]),NULL,reader,NULL);
		if(err!=0){
			fprintf(stderr,"Error creating thread reader %d\n", i);
		}
	}
	for (int i=0; i<argwriter;i++){//create writers threads
		err=pthread_create(&(thread_writers[i]),NULL,writer,NULL);
		if(err!=0){
			fprintf(stderr,"Error creating thread writer %d\n", i);
		}
	}
	
	//TO DO  destroy mutexes and semaphores
	return 0;
}