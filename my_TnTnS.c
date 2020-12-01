/*
 *Implementation of the test-and-test-and-set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include "my_TnTnS.h" 
void lock (TnTnS_t *mylock){
	while (exchange(mylock, 1)) {//we try to get the lock
 		 while (*mylock==1) {}//we didn't get it, we won't try to get it again while the lock is still in use
	}
}
void unlock(TnTnS_t *mylock){
	exchange(mylock,0);
}
int exchange(TnTnS_t *mylock,int i){
	int ax=i;
	asm(    "movl %1, %%eax;"
                "xchgl %%eax, %0;"//atomic instruction to exchange value of eax and our lock value
                "movl %%eax, %1;"
                :
                :"m" (mylock), "m" (ax)
                :"eax"
        );
	return ax;
}
int main (){
	TnTnS_t i=0;
        int my_var=0;
        lock(&i);
                puts("locked");
                my_var ++;
        unlock(&i);
        puts("unlocked");
        return 0;
}
