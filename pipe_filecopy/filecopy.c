/* Design a file-copying program named filecopy using ordinary pipes.
This program will be passed two parameters: the name of the file to be
copied and the name of the copied file. The program will then create
an ordinary pipe and write the contents of the file to be copied to the
pipe. The child process will read this file from the pipe and write it to
the destination file. For example, if we invoke the program as follows:
filecopy input.txt copy.txt
the file input.txt will be written to the pipe. The child process will
read the contents of this file and write it to the destination file copy.txt .
You may write this program using either UNIX or Windows pipes.*/
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define WRITE_END 1
#define READ_END 0

volatile sig_atomic_t sig_rec=0;

void catch_sig(int signum){
	printf("\nerror during source opening,abort\n");
	sig_rec=1;
}

int equals(char* str1,char*str2){
	int res=1;
	if(strlen(str1)!=strlen(str2)){
		res=0;
	}
	for(int i=0;i<strlen(str1)+1 && res==1;i++){
		res=(str1[i]==str2[i])?res:0;
	}
	return res;
}

int main(int argc,char ** argv){
	int fd[2];
	int fd_s_d;
	char temp;
	pid_t pid;
	if(argc<2 || argc>3 || (argc==2 && !equals(argv[1],"-h") && !equals(argv[1],"--help"))){
		printf("wrong arguments, type filecopy -h or filecopy --help\n");
		//printf("\n%s\n",strerror(errno));
		exit(1);
	}
	if(argc==2){
		printf("type filecopy <source> <dest>  if dest exists override it with source, otherwise create dest and copy source\n");
		exit(0);
	}
	if(pipe(fd)==-1){
		printf("%s\n",strerror(errno));
		return 1;
	}
	pid=fork();
	if(pid<0){
		printf("%s\n",strerror(errno));
		return 1;
	}
	if(pid==0){
		close(fd[WRITE_END]);
		struct sigaction action;
		memset(&action,0,sizeof(action));
		action.sa_handler = catch_sig;
		sigaction(SIGTERM,&action,NULL);
		fd_s_d=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC);
		if(fd_s_d==-1){
			printf("%s\n",strerror(errno));
			close(fd[READ_END]);
			return 1;
		}
		while(read(fd[READ_END],&temp,1)!=0){
			write(fd_s_d,&temp,1);
		}
		close(fd_s_d);
		close(fd[READ_END]);
		if(sig_rec==1){
			unlink(argv[2]);//smthing strange happens here, but the program still works
		}
	}else{
		close(fd[READ_END]);
		fd_s_d=open(argv[1],O_RDONLY);
		if(fd_s_d==-1){
			printf("%s\n",strerror(errno));
			kill(pid,SIGTERM);
			close(fd[WRITE_END]);
			return(1);
		}
		while(read(fd_s_d,&temp,1)!=0){
			write(fd[WRITE_END],&temp,1);
		}
		close(fd_s_d);
		close(fd[WRITE_END]);
		wait(NULL);
	}

}
