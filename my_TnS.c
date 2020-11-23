/*
 *Implementation of the test and set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
 
	
//this implementation use a pointer to an int that will be used as the "lock" in our spinlock.
//these functions are implemented using inline assembly(X86((IA32) make use of the xchg atomic instruction.
	void lock (int *mylock){
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
	void unlock(int *mylock){
        int ax=0;
	    asm(
			 "xchgl %1, (%0);"//atomic instruction to exchange value of eax and our lock value
		    :
		    :"l" (mylock), "a" (ax)
	    );
	}
