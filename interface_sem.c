#include <stdio.h>
#include <stdlib.h>
#include "my_TnS.h"
#include "my_semaphore.h"
    
void lock ( TnS_t *mylock){
    int ax=1;
    while (ax==1){
	ax=1;
	asm(	"movl %1, %%eax;"
		"xchgl %%eax, %0;"//atomic instruction to exchange value of eax and our lock value
    		"movl %%eax, %1;"
		:
    		:"m" (mylock), "m" (ax)
		:"eax"
	);
    }
}
void unlock(TnS_t *mylock){
	int ax=0;
	asm(	"movl %1, %%eax;"
		"xchgl %%eax, %0;"//atomic instruction to exchange value of eax and our lock value
		:
		:"m" (mylock), "m" (ax)
		:"eax"
	);
}

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
