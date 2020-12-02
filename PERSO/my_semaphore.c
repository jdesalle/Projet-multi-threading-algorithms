#include <stdio.h>
#include <stdlib.h>
#include "../DEP/my_TnTnS.h"
#include "../DEP/my_semaphore.h"

void my_sem_init(my_sem_t *s, int c){
    s->count = c;
    init(&(s->mutex));
}

void my_sem_wait(my_sem_t *s){
    lock(&(s->mutex));
    while(s->count == 0);
    s->count--;
    unlock(&(s->mutex));
}

void my_sem_post(my_sem_t *s){
    lock(&(s->mutex));
    s->count++;
    unlock(&(s->mutex));
}
