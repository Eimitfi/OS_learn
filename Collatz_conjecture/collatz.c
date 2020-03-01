#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>
#define MAX_NUMBERS 100
#define NAME "OS"
#define BYTES() (sizeof(int)*MAX_NUMBERS)
//establish shared memory
//run 
//print
//rem shared
int get_number(char * arg){
	int res=0;
	for(int i=0;arg[i]!='\0';i++){
		if(arg[i]<'0' || arg[i]>'9'){
			printf("the argument is not a number or is a negative one\n");
			exit(1);
		}
		res=res*10+(arg[i]-'0');
	}
	return res;
}

int main(int argc,char *argv []){
	int shm_fd;
	int *ptr;
	pid_t pid;
	int num;
	if(argc!=2){
		printf("wrong arguments,insert a number pls\n");
		exit(1);
	}
	num=get_number(argv[1]);
	shm_fd=shm_open(NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, BYTES());
	ptr=(int *)mmap(0, BYTES(),PROT_WRITE, MAP_SHARED, shm_fd,0);
	pid=fork();
	if(pid<0){
		printf("error during fork creation\n");
		exit(2);
	}
	if(pid==0){
		int *n=NULL;
		int size=0;
		for(;num>1;num=(num%2==0)?(num/2):(3*num+1)){
				if(size==MAX_NUMBERS){
					free(n);
					abort();
				}
				n=(int*)realloc(n,(size+1)*sizeof(int));
				n[size++]=num;
		}
		n=(int *)realloc(n,(size+1)*sizeof(int));
		n[size++]=num;
		ptr[0]=size;
		ptr++;;
		for(int i=0;i<size;i++){
			(*ptr)=n[i];
			ptr++;
		}
		free(n);
	}else{
		int dim;
		int status;
		wait(&status);
		if(!WIFEXITED(status)){
			printf("the numbers needed are more than MAX_NUMBERS,increase MAX_NUMBERS");
			shm_unlink(NAME);
			exit(0);
		}
		dim=ptr[0];
		ptr++;
		for(int i=0;i<dim;i++){
			printf("%d ",(ptr)[i]);
		}
		shm_unlink(NAME);
	}
}
