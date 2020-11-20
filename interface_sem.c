#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

interface my_semaphore{
    struct{
        int count;
        pthread_cond_t wait;
        pthread_mutex_t lock
    } my_sem_t;

    void my_sem_init(my_sem_t *s, int c){
        s->count = c;
        pthread_cond_init(&(s->wait), NULL);
        phtread_mutex_init(&(s->lock), NULL);
        return;
    }

    void my_sem_wait(my_sem_t *s){
        pthread_mutex_lock(&(s->lock));
        s->count--;
        if (s->count < 0){
            pthread_cond_wait(&(s->wait), &(s->lock));
        }
        pthread_mutex_unlock(&(s->lock));
        return;
    }

    void my_sem_signal(my_sem_t *s){
        pthread_mutex_lock(&(s->lock));
        s->count++;
        if (s.count <= 0){
            pthread_cond_signal(&(s->wait));
        }
        pthread_mutex_unlock(&(s->lock));
    }
}