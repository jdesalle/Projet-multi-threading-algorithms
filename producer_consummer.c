#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>

#define slots 8
int MAX_PROD;
int MAX_CONS;

pthread_mutex_t mutex; 
sem_t empty;
sem_t full;

int count_c = 0;
int count_p = 0;

int first = 0; // index of the first data to consume
int last = 0; // index of the next data to produce

int buffer[slots];

int nb_rand(){
    union {
        int i;
        unsigned char uc[sizeof(int)];
    } u;
    for (size_t i = 0; i < sizeof(u.uc); i++){
        u.uc[i] = rand();
    }
    return u.i;
}

void *producer(void* args){
    // insertion
    int i = 0;
    while(i < 1024/MAX_PROD){
        sem_wait(&empty); //producer must wait until one slot is empty
        pthread_mutex_lock(&mutex); //lock buffer
        buffer[last] = nb_rand();
        printf("The item %d has been produced and placed at the position %d\n", buffer[last], last);
        last = (last+1)%slots; //we move to the next slot
        count_p++;
        while(rand() > RAND_MAX/10000);
        pthread_mutex_unlock(&mutex); //unlock buffer
        sem_post(&full); //wakeup the consumer
        i++;
    }
    pthread_exit(NULL);
}

void *consumer(void* args){
    //extraction
    int j = 0;
    while(j < 1024/MAX_CONS){
        sem_wait(&full); //consumer must wait until producer added something
        pthread_mutex_lock(&mutex);
        int x = buffer[first];
        printf("We consumed the item %d at position %d\n", x, first);
        first = (first+1)%slots;
        count_c++;
        while(rand() > RAND_MAX/10000);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); //wakeup the producer
        j++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    MAX_CONS = atoi(argv[1]);
    MAX_PROD = atoi(argv[2]);

    printf("Nombre cons : %d\n", MAX_CONS);
    printf("Nombre prod : %d\n", MAX_PROD);
    
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

    printf("Count_c : %d\n", count_c);
    printf("Count_p : %d\n", count_p);

    return 0;
}
