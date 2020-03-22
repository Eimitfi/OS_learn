#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	char temp,temp1;
	int fd;
	int i=0;
	char str[80];
	const char * fifo1="/root/Documents/OS_learn/pipe_reverse/fifo1";
	const char * fifo2="/root/Documents/OS_learn/pipe_reverse/fifo2";
//	if(mkfifo(fifo1,0666)==-1 || mkfifo(fifo2,0666)==-1){ no need to create it
//		printf("\n%s\n",strerror(errno));
//		exit(1);
//	}
	fd=open(fifo1,O_RDONLY);
	while(0<read(fd,&temp,1) && temp!='\0' && i<79){
		temp1=tolower(temp);
		temp=(temp1==temp)?toupper(temp):temp1;
		str[i]=temp;
		i++;
	}
	str[i++]='\0';
	close(fd);
	unlink(fifo1);
	fd=open(fifo2,O_WRONLY);
	write(fd,str,strlen(str)+1);
	close(fd);
}
