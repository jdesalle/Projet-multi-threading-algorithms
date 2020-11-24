#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
     int a=0;
typedef int TnS_t;
TnS_t  locker=0;
	void TnS_lock ( TnS_t *mylock){
	    int ax=1;
	    while(ax==1) {
	        ax=1;
	    	asm(
	                "xchgl %1, %0;"//atomic instruction to exchange value of eax and our lock value
		    	:
		    	:"l" (*mylock), "a" (ax)
	    	);
	    }
	}
	void TnS_unlock(TnS_t *mylock){
        int ax=0;
	    asm(
			 "xchgl %1, (%0);"//atomic instruction to exchange value of eax and our lock value
		    :
		    :"l" (mylock), "a" (ax)
	    );
	}
void *adder(void *arg){
   TnS_lock(&locker);
  puts("entered");
   a++;
    printf("%d\n",a);
   TnS_unlock(&locker);
}
int main(){


    pthread_t phil[4];
    pthread_create(&(phil[0]),NULL,adder,NULL);
    pthread_create(&(phil[1]),NULL,adder,NULL);
    pthread_create(&(phil[2]),NULL,adder,NULL);

	
 
}
