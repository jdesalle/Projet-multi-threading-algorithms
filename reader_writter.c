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
sem_t wread;//block writers
sem_t sread;//block readers
int readers=0;//number of reader currently reading
int writers=0;//number of writers waiting
int nread=0;//number of reading already done (shoudl go to 2560)
int nwrite=0;//number of writing alreadydone.(should go to 640)

void reader(void *args){
	
}
void writers(void *args){
	
}
int maint (int argc, char* argv[]){
	return 0
}