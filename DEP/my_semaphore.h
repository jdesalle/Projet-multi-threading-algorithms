#include<stdio.h>
#include<stdlib.h>
#include "my_TnTnS.h"

typedef struct{
    int count;
    TnTnS_t mutex;
} my_sem_t;

void my_sem_init(my_sem_t *s, int n);
void my_sem_wait(my_sem_t *s);
void my_sem_post(my_sem_t *s);
