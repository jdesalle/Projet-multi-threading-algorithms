/*
 *Implementation of the test and set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<stdlib.h>

typedef int TnTnS_t;//our lock actualy use an int, but for the sake code lisiblity we use th TnS_t type.
//these functions are implemented in inline assembly(x86(IA32)) make use of the xchg atomic instruction.
void lock (TnTnS_t *mylock);
void unlock(TnTnS_t *mylock);
void init(TnTnS_t *mylock);
int exchange(TnTnS_t *mylock, int i);

