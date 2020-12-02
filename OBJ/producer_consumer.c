#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define slots 8
int NPROD;
int NCONS;

pthread_mutex_t mutex; 
sem_t empty;
sem_t full;

// int count_c = 0; // à supprimer plus tard (check si on fait bien 1024)
// int count_p = 0;

int n_prod = 1; // incrémentés dès que un item est produit/consommé
int n_cons = 1;

int first = 0; // index of the first data to consume
int last = 0; // index of the next data to produce

int *buffer;

int nb_rand(){
    int s = rand()%2;
    if (s == 1){
        return rand()%(INT_MAX);
    }
    return -(rand()%(INT_MAX));
}

void my_time_spent(){
    while(rand() > RAND_MAX/10000);
}

void *producer(void* args){
    // insertion
    while(n_prod < 1024 - NPROD + 2){
        sem_wait(&empty); //producer must wait until one slot is empty
        pthread_mutex_lock(&mutex); //lock buffer
        buffer[last] = nb_rand();
        // printf("The item %d has been produced and placed at the position %d\n", buffer[last], last);
        last = (last+1)%slots; //we move to the next slot
        // count_p++;
        // printf("Count_p = %d\n", count_p);
        pthread_mutex_unlock(&mutex); //unlock buffer
        // printf("mutex unlocked\n");
        sem_post(&full); //wakeup the consumer
        // printf("sem post full\n");
        my_time_spent();
        // printf("time spent\n");
        n_prod++;
    }
    // printf("Thread_p exited\n");
    pthread_exit(NULL);
}

void *consumer(void* args){
    //extraction
    while(n_cons < 1024 - NCONS + 2){
        sem_wait(&full); //consumer must wait until producer added something
        pthread_mutex_lock(&mutex);
        // printf("we consumed the item %d at position %d\n", buffer[first], first);
        buffer[first] = 0;
        // printf("We consumed the item at position %d\n", first);
        first = (first+1)%slots;
        // count_c++;
        // printf("Count_c = %d\n", count_c);
        pthread_mutex_unlock(&mutex);
        // printf("mutex unlocked\n");
        sem_post(&empty); //wakeup the producer
        // printf("sem_post empty\n");
        my_time_spent();
        // printf("time spent\n");
        n_cons++;
    }
    // printf("Thread_c exited\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    int NTHREAD = atoi(argv[1]);

    if (NTHREAD%2 == 0){
        NCONS = NTHREAD/2;
        NPROD = NTHREAD/2;
    }
    else{
        NCONS = (NTHREAD/2)+1;
        NPROD = NTHREAD/2;
    }

    // printf("Nombre cons : %d\n", NCONS);
    // printf("Nombre prod : %d\n", NPROD);
    
    // initialize semaphore for empty slots,
    // upon start up all slots are empty
    // producers may hence write in the buffer

    //initialize semaphore for full slots
    //upon start up the buffer is empty
    //consumer may hence not  extract data
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, slots);
    sem_init(&full, 0, 0);

    buffer = (int*) malloc(9 * sizeof(int));

    //init consumer thread
    //init producer thread
    pthread_t cons[NCONS];
    pthread_t prod[NPROD];

    for(int i = 0; i < NPROD; i++){
        pthread_create(&prod[i], NULL, producer, NULL);
    }

    for(int i = 0; i < NCONS; i++){
        pthread_create(&cons[i], NULL, consumer, NULL);
    }

    //wait until prod and cons finish their jobs
    for(int i = 0; i < NPROD; i++){
        pthread_join(prod[i], NULL);
        // printf("Thread_p %d joint\n", i);
    }

    for(int i = 0; i < NCONS; i++){
        pthread_join(cons[i], NULL);
        // printf("Thread_c %d joint\n", i);
    }

    //destroy mutex
    pthread_mutex_destroy(&mutex);
    // printf("mutex destroyed\n");

    //destroy semaphores
    sem_destroy(&empty);
    // printf("empty destroyed\n");
    sem_destroy(&full);
    // printf("full destroyed\n");

    // printf("Count_c : %d\n", count_c);
    // printf("Count_p : %d\n", count_p);

    return EXIT_SUCCESS;
}
