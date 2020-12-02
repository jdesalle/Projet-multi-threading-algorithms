#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include"DEP/my_TnS.h"
int n=5;
int r=5;
TnS_t mylock;
void *test(void *arg);
int main(int argc,char *argv[]){
        char ch;
	init(&mylock);
        int err;
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
	pthread_t testers[n];
	 for (int i=0; i<n;i++){
                err=pthread_create(&testers[i],NULL,test,NULL);
                if(err!=0){
                        fprintf(stderr,"Error creating thread %d",i);
                }
        }
	for (int i=0;i<n;i++){
		pthread_join(testers[i],NULL);
	}
	return 0;
}
void *test(void *arg){
	for (int i=0;i<r/n;i++){
		lock(&mylock);
puts("locked");
		unlock(&mylock);
puts("unlocked");
		while(rand()>RAND_MAX/10000);//simulate an access while allowing the next access immediately
	}
	pthread_exit(NULL);

}

