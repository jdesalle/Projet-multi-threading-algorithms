#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef int buffer_item;

#define slots 8
#define MAX_PROD 4
#define MAX_CONS 4

pthread_mutex_t mutex; 
sem_t empty;
sem_t full;

int first = 0; // index of the first data to consume
int last = 0; // index of the next data to produce

buffer_item buffer[slots];

int item = 0;

void *producer(void* args){
    // insertion
    for (int i = 0; i < slots; i++){
        sem_wait(&empty); //producer must wait until one slot is empty
        pthread_mutex_lock(&mutex); //lock buffer
        buffer[last] = item;
        printf("The item %d has been produced and placed at the position %d\n", item, last);
        last = (last+1)%slots; //we move to the next slot
        item++;   
        pthread_mutex_unlock(&mutex); //unlock buffer
        sem_post(&full); //wakeup the consumer
    }
    pthread_exit(NULL);
}

void *consumer(void* args){
    //extraction
    for(int i = 0; i < slots; i++){
        sem_wait(&full); //consumer must wait until producer added something
        pthread_mutex_lock(&mutex);
        int x = buffer[first];
        printf("We consumed the item %d at position %d\n", x, first);
        first = (first+1)%slots; //we move to the next data
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); //wakeup the producer
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    
    // initialize semaphore for empty slots,
    // upon start up all slots are empty
    // producers may hence write in the buffer

    //initialize semaphore for full slots
    //upon start up the buffer is empty
    //consumer may hence not  extract data
    if(sem_init(&empty, 0, slots) || sem_init(&full, 0, 0)){
        perror("");
    }

    //init consumer thread
    //init producer thread
    pthread_t cons[MAX_CONS], prod[MAX_PROD];

    for(int i = 0; i < MAX_CONS; i++){
        if(pthread_create(&cons[i], NULL, consumer, NULL)){
            perror("");
        }
    }

    for(int i = 0; i < MAX_PROD; i++){
        if(pthread_create(&prod[i], NULL, producer, NULL)){
            perror("");
        }
    }


    //wait until prod and cons finish their jobs
    for(int i = 0; i < MAX_CONS; i++){
        if(pthread_join(cons[i], NULL)){
            perror("");
        }
    }

    for(int i = 0; i < MAX_PROD; i++){
        if(pthread_join(prod[i], NULL)){
            perror("");
        }
    }

    //destroy semaphores
    if(sem_destroy(&full) || sem_destroy(&empty)){
        perror("");
    }

    //destroy mutex
    if(pthread_mutex_destroy(&mutex)){
        perror("");
    }

    return 0;
}
