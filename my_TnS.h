/*
 *Implementation of the test and set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<stdlib.h>

//this implementation use a pointer to an int that will be used as the "lock" in our spinlock.
//these functions are implemented in inline assembly(x86(IA32)) make use of the xchg atomic instruction.
void lock (int *mylock);
void unlock(int *mylock);