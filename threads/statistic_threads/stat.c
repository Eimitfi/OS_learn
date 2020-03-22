#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define THREADS_NUMBER 3 //each thread is assigned to a task, if u want to add a task increase this number
int len;
int* int_arg;
double avr;
int max_v,min_v,count;
void * (*func[THREADS_NUMBER])(void *);
void * prepare(void *param);
void * average(void* param);
void * max(void* param);
void * min(void* param);

int main(int argc,char**argv){
	if(argc==1){
		printf("no numbers have been specified\n");
		return 1;
	}
	func[0]=average;//not scalable but i'm lazy
	func[1]=max;
	func[2]=min;
	count=0;
	pthread_t tid[THREADS_NUMBER];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	len=argc-1;
	++argv;
	int_arg=(int*)malloc(sizeof(int)*len);
	for(int i=0;i<len;i++){
		int_arg[i]=atoi(argv[i]);
	}
	for(int i=0;i<THREADS_NUMBER;i++){
		pthread_create(tid+i,&attr,prepare,NULL);
	}
	for(int i=0;i<THREADS_NUMBER;i++){
		pthread_join(*(tid+i),NULL);
	}
	printf("average: %f\nmax: %d\nmin: %d\n",avr,max_v,min_v);


}

void * prepare(void * param){
	printf("thread %d ready to work\n",count+1);
	func[count++](NULL);
}

void * min(void * param){
	min_v=int_arg[0];
	for(int i=1;i<len;i++){
		min_v=(int_arg[i]<min_v)?int_arg[i]:min_v;
	}
	pthread_exit(0);
}

void * max(void * param){
	max_v=int_arg[0];
	for(int i=1;i<len;i++){
		max_v=(int_arg[i]>max_v)?int_arg[i]:max_v;
	}
	pthread_exit(0);
}

void * average(void * param){
	int sum=0;
	for(int i=0;i<len;i++){
		sum+=int_arg[i];
	}
	avr=((double)sum)/len;
	pthread_exit(0);
}
