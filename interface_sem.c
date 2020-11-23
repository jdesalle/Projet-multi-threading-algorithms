#include <stdio.h>
#include <stdlib.h>

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
    int lock;
} my_sem_t;

void my_sem_init(my_sem_t *s, int c){
    s->count = c;
    s->lock = 0;
}

void my_sem_wait(my_sem_t *s){
    while(1){
        while(myLock());
        if (s->count > 0){
            s->count--;
            s->lock = 0;
            return;
        }
        else{
            s->lock = 0;
        }
    }
}

void my_sem_post(my_sem_t *s){
    myLock();
    s->count++;
    myUnlock();
}