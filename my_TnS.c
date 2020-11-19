/*
 *Implementation of the test and set algorithm realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
 
 
	asm("lock: ;"
			"movl (%esp), %ecx;"//put the pointer to our lock passed as argument in ecx 
			"movl $1, %eax;" // set eax to 1
			"xchgl %eax, ($ecx);"//atomic instruction to exchange value of eax and our lock value
			"testl %eax, %eax;" //test if eax==0 -> if that's the case, the lock is still used by another thread
			"jnz lock;" //loop back to the begining of our function while the lock is still in use
		"ret;"
	);

	asm(	
		"unlock: ;"
		    "movl (%esp), %ecx;"// put the pointer to our lock passed as argument in ecx 
			"movl $0, %eax;" // set eax to 0
			"xchgl %eax, (%ecx); "//atomic instruction to exchange value of eax and our lock value
			//this xchg operation is the one that actually unlock TnS lock. 
			"ret"
	);