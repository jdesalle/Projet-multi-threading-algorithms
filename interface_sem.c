#include <stdio.h>
#include <stdlib.h>

int verrou = 0;

void my_lock(){
    int start = 1;
    asm("xchlg %1, %0;"
        :"=&r"(verrou)
        :"r"(start)
    );
    if (start == 0){
        myLock();
    }
    return;
}

void my_unlock(){
    int end = 0;
    asm("xchlg %1, %0;"
        :"=&r"(verrou)
        :"r"(end)
    );
    return;
}

typedef struct{
    int count;
} my_sem_t;

void my_sem_init(my_sem_t *s, int c){
    s->count = c;
}

void my_sem_wait(my_sem_t *s){
    myLock();
    s->count--;
    while (s->count < 0);
    myUnlock();
}

void my_sem_post(my_sem_t *s){
    myLock();
    s->count++;
    myUnlock();
}