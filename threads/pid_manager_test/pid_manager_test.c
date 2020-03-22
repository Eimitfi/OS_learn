#include "../../pid_manager/pid_manager.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#define N_THREADS() BIT_NEEDED()+1

void * runner(void * arg){
	int my_pid;
	while((my_pid=allocate_pid())==1){
		printf("failed, no pids avaliable ...retrying...\n");
		sleep(rand()%5+1);
	}
	printf("pid %d taken\n",my_pid);
	sleep(rand()%30+1);
	release_pid(my_pid);
	printf("pid %d released\n",my_pid);
	pthread_exit(0);
}

int main(){
	if(allocate_map()==-1){
		printf("error allocating the map\n");
		return 1;
	}
	srand(time(NULL));
	pthread_t tid[N_THREADS()];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(int i=0;i<N_THREADS();i++){
		pthread_create(tid+1,&attr,runner,NULL);
	}
	pthread_exit(NULL);

}
