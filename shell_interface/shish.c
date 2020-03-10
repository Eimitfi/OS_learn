#include "util.h"

int toggle_ret(char* tmp){ //cuts the string when a return is encountered
	int i;
	for(i=0;tmp[i]!='\0' && i<MAX_LINE;i++){
		if(tmp[i]=='\n'){
			tmp[i]='\0';
			return i;
		}
	}
	return i;

}

void toggle_sp(char*tmp,unsigned int * dim){//cuts the spaces at the beginning and end of the string
	int i=0;
	int n,d;
	while(tmp[i]==' '){
		n=i+1;
		d=i;
		while(n<(*dim)){
			tmp[d++]=tmp[n++];
		}
		(*dim)--;
		tmp[(*dim)]='\0';
	}
	while(tmp[(*dim)-1]==' '){
		(*dim)--;
		tmp[(*dim)]='\0';
	}
}

boolean wait_children(char * tmp,int * dim){
        if(tmp[(*dim)-1]=='&'){
                (*dim)--;
                tmp[(*dim)]='\0';
                toggle_sp(tmp,dim);
                return true;
        }
        return false;
}

char ** parse(char**arg,char*tmp,int * num){
	int i=0,count=0,x;
	while(tmp[i]!='\0'){
		x=0;
		arg=(char**)realloc(arg,sizeof(char*)*(++count));
		arg[count-1]=(char*)malloc(sizeof(char)*MAX_LINE);
		while((tmp[i]!=' ' && tmp[i]!='\0') && x<MAX_LINE){
			arg[count-1][x++]=tmp[i++];
		}
		i=(tmp[i]==' ')?i+1:i;
		arg[count-1][x]='\0';
	}
	arg=(char**)realloc(arg,sizeof(char*)*(++count));
	arg[count-1]=NULL;
	(*num)=count;
	return arg;
}

int main(){
	pid_t pid;
	char tmp[MAX_LINE];
	char ** arg=NULL;
	clear_screen();
	atexit(clear_screen);
	boolean background;
	while(1){
		write(STDOUT_FILENO,"shish>",6);
		if(fgets(tmp,MAX_LINE,stdin)==NULL){
			printf("%s\n",strerror(errno));
			exit(1);
		}
		real_dim=toggle_ret(tmp);
		toggle_sp(tmp,&real_dim);
		if(strcmp(tmp,"exit")==0 || strcmp(tmp,"quit")==0){
			return 0;
		}
		background=wait_children(tmp,&real_dim);
		pid=fork();
		if(pid<0){
			printf("%s\n",strerror(errno));
			exit(1);
		}
		if(pid==0){
			int count;
			arg=parse(arg,tmp,&count);
			if(count){
				if(-1==execvp(arg[0],arg)){
					printf("%s\n",strerror(errno));
				}
			}
		
		_exit(0);
		}
		if(!background){
			wait(NULL);
		}
	}

}
