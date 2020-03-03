#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(){
	char temp;
	int i=0,fd;
	char str[80];
	const char * fifo1="/root/Documents/OS_learn/pipe_reverse/fifo1";
	const char * fifo2="/root/Documents/OS_learn/pipe_reverse/fifo2";
	if(-1==mkfifo(fifo1,0666) || -1==mkfifo(fifo2,0666)){
		printf("\n%s\n",strerror(errno));
		exit(1);
	}
	printf("inserisci: ");
	fgets(str,80,stdin);
	fd=open(fifo1,O_WRONLY);
	write(fd,str,strlen(str)+1);
	close(fd);
	fd=open(fifo2,O_RDONLY);
	while(read(fd,&temp,1)>0 && i<strlen(str+1)){
		str[i]=temp;
		i++;
	}
	close(fd);
	unlink(fifo2);
	printf("\n%s",str);
}
