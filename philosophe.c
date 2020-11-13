

int n=5;
pthread_mutex_t chopstick[n];
pthread_t phil[n];
//take an argument for number of philosohers (threads) with the option -t
int main(int argc,char *argv[]){
	while ((ch=getopt(argc, argv, "t:")) !=  EOF){
		switch(ch){
			case 't':
				n=optarg;
				break;
			default:
				fprintf(stderr, "invalid argument");
		}
	}
	//Two structures: chopstick and phil respectively representing the chopsticks and the philosophers
	//chopstick will be used for the mutexe's checking that each philosophe can access to his chopstick 
	//phil will contain each thread representing a philosopher]
	for (int i=0; i<n;i++){
		err=pthread_create(&(phil[i]),NULL,philosopher(&i),NULL);
		if(err!=0){
			fprintf(stderr,"Error creating thread %d\n", i);
		}
	}
	return 0;
	
}
//take its id as an argument. operate 10k cyles of eating/thinking without pauses.
void* philosophe(void* arg){
	//id also correspond to the lef chopstick
	int id=*((int *)arg);
	int right=(id+1)%n);
	for (int i=0;i<10000;i++){
		printf("philophe %d is thinking",id);
		//if id is pair, begin with left chopstick, otherwise begin with right (to avoid deadlock)
		if((id&&0b)1==0){
			pthread_mutex_lock(&chopstick[id]);
			pthread_mutex_lock(&chopstick[right]);
		}
		else{
			pthread_mutex_lock(&chopstick[right]);
			pthread_mutex_lock(&chopstick[id]);
		}
		printf("philophe %d is eating",id);
		pthread_mutex_unlock(&chopstick(id));
		pthread_mutex_unlock(chopstick(right));
	}
} 
