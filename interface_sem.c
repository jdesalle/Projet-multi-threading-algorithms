#include <stdio.h>
#include <stdlib.h>
#include "my_TnS.h"
    
void lock(TnS_t *mylock){
    int ax;
    do {
        ax=1;
    	asm(
		"xchgl %1, (%0);"//atomic instruction to exchange value of eax and our lock value
    		:
    		:"l" (mylock), "a" (ax)
	);
	 }while(ax==0);
}
void unlock(TnS_t *mylock){
	int ax=0;
	asm(
		"xchgl %1, (%0);"//atomic instruction to exchange value of eax and our lock value
		:
		:"l" (mylock), "a" (ax)
	);
}

typedef struct{
    int count;
} my_sem_t;

void my_sem_init(my_sem_t *s, int c){
    s->count = c;
}

void my_sem_wait(my_sem_t *s){
    while(1){
        while(myLock());
        if (s->count > 0){
            s->count--;
            return;
        }
    }
}

void my_sem_post(my_sem_t *s){
    myLock();
    s->count++;
    myUnlock();
}
