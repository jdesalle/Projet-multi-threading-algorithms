#include<stdio.h>
#include<stdlib.h>

typedef int TnS_t;//our lock actualy use an int, but for the sake code lisiblity we use th TnS_t type.
//these functions are implemented in inline assembly(x86(IA32)) make use of the xchg atomic instruction.
void lock (TnS_t *mylock);
void unlock(TnS_t *mylock);
void init(TnS_t *mylock);
