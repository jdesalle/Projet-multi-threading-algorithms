/*
 *Implementation of the philosophers's dinner problem realised for the course "LINFO1252:Computer Systems" given by 
 *prof E.Riviere at the Université Catholique de Louvain(UCLouvain), in Belgium. This implementation was written by 
 *pair 3-8 composed of Jonathan de Salle and Philippine de Suraÿ in 2020.
 */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include"../DEP/my_TnTnS.h"
int n=5;//number of philosophers
int r=5; // number of repetions
TnTnS_t *chopstick;//actual chopstick array used by the thread

void* philosopher(void* arg);
//take an argument for number of philosohers (threads) with the option -t
//and number of repetitions with -r
int main(int argc,char *argv[]){
	char ch;
	while ((ch=getopt(argc, argv, "t:r:")) !=  EOF){
		switch(ch){
			case 't':
				n=atoi(optarg);
				break;
			case 'r':
				r=atoi(optarg);
				break;
			default:
				fprintf(stderr, "invalid argument");
		}
	}
	//Two structures: chopstick and phil respectively representing the chopsticks and the philosophers
	//chopstick will be used for the mutexe's checking that each philosophe can access to his chopstick 
	//phil will contain each thread representing a philosopher]
	TnTnS_t chopsticks[n];//this one allow us to create an array of element of size unknown at compile time
	pthread_t phil[n];
	int err;
	for (int i=0;i<n;i++){
		init(&chopsticks[i]);
	}
	chopstick=chopsticks;//we link this array to ou static pointer, so each thread can use it
	for (int i=0; i<n;i++){
		int id=i;
		err=pthread_create(&phil[i],NULL,philosopher,(void *) &id);
		if(err!=0){
			fprintf(stderr,"Error creating thread %d",id);
		}
	}
	for (int i=0; i<n;i++){
		pthread_join(phil[i],NULL);
	}
	//check destroying mutex
	return 0;
}
//take its id as an argument. operate 10k cycles of eating/thinking without pauses.
void* philosopher(void* arg){
	//id also correspond to the left chopstick
	int id=*((int *)arg);
	int right=((id+1)%n);//allow us to circle for the last philosopher
	for (int i=0;i<r;i++){
		printf("philosophe %d is thinking\n",id);
		//if id is pair, begin with left chopstick, otherwise begin with right (to avoid deadlock)
		if((id&&0b1)==0){
			lock(&chopstick[id]);
printf("philosopher %d locked chopstick left\n",id);
			lock(&chopstick[right]);
printf("philosopher %d locked chopstick right\n",id);

		}
		else{
			lock(&chopstick[right]);
printf("philosopher %d locked chopstick right\n",id);
			lock(&chopstick[id]);
printf("philosopher %d locked chopstick left\n",id);
		}
		printf("philosophe %d is eating\n",id);
		unlock(&chopstick[id]);
		unlock(&chopstick[right]);
	}
	pthread_exit(NULL);
}

