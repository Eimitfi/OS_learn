#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
pid_t pid;
pid=fork();
if(pid<0){
	printf("zio cane");
}else if(pid==0){
	printf("the children has slept");
}else{
	sleep(30);
	wait(NULL);
	printf("the children is dead");
}
return 0;
}
