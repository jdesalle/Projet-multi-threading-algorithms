

int main(int argc,char *argv[]){
	int N=5;
	while ((ch=getopt(argc, argv, "t:")) !=  EOF){
		switch(ch){
			case 't':
				N=optarg;
				break;
			default:
				fprintf(stderr, "invalid argument");
		}
	}
	sem_t chopsticks;
	pthread_t  threads [N];
	for (int i =0; i<N;i++){
		err2=pthread_create(&(thread[i]),NULL,philosopher(i),NULL);
		if(err!=0){
			error(err, "phtread create");
		}
	}
	return 0;
}
void philosopher(int id){

}
