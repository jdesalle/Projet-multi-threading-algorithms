/*
 *Implementation of the test and set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
 
	
//this implementation use a pointer to an int that will be used as the "lock" in our spinlock.
//these functions are implemented using inline assembly(X86((IA32) make use of the xchg atomic instruction.
#include "my_TnS.h"
    
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
void init(TnS_t *my_lock){
	*my_lock=0;
}

int main (){
	TnS_t i=0;
	int my_var=0;
	lock(&i);
		puts("locked");
		my_var ++;
	unlock(&i);
	puts("unlocked");
	return 0;
}
