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

int count_c = 0; // à supprimer plus tard (check si on fait bien 1024)
int count_p = 0;

int n_prod = 0; // incrémentés dès que un item est produit/consommé
int n_cons = 0;

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
    while(n_prod <= 1024 - MAX_PROD){
        sem_wait(&empty); //producer must wait until one slot is empty
        pthread_mutex_lock(&mutex); //lock buffer
        buffer[last] = nb_rand();
        printf("The item %d has been produced and placed at the position %d\n", buffer[last], last);
        last = (last+1)%slots; //we move to the next slot
        count_p++;
        n_prod++;
        while(rand() > RAND_MAX/10000);
        pthread_mutex_unlock(&mutex); //unlock buffer
        sem_post(&full); //wakeup the consumer
    }
    pthread_exit(NULL);
}

void *consumer(void* args){
    //extraction
    while(n_cons <= 1024 - MAX_CONS){
        sem_wait(&full); //consumer must wait until producer added something
        pthread_mutex_lock(&mutex);
        int x = buffer[first];
        printf("We consumed the item %d at position %d\n", x, first);
        first = (first+1)%slots;
        count_c++;
        n_cons++;
        while(rand() > RAND_MAX/10000);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); //wakeup the producer
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
    sem_init(&empty, 0, slots);
    sem_init(&full, 0, 0);

    //init consumer thread
    //init producer thread
    pthread_t cons[MAX_CONS], prod[MAX_PROD];

    for(int i = 0; i < MAX_CONS; i++){
        pthread_create(&cons[i], NULL, consumer, NULL);
    }

    for(int i = 0; i < MAX_PROD; i++){
        pthread_create(&prod[i], NULL, producer, NULL);
    }


    //wait until prod and cons finish their jobs
    for(int i = 0; i < MAX_CONS; i++){
        pthread_join(cons[i], NULL);
    }

    for(int i = 0; i < MAX_PROD; i++){
        pthread_join(prod[i], NULL);
    }

    //destroy semaphores
    sem_destroy(&full);
    sem_destroy(&empty);

    //destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("Count_c : %d\n", count_c);
    printf("Count_p : %d\n", count_p);

    return 0;
}
