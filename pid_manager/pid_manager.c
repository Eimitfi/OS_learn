#include "pid_manager.h"
static unsigned int * bit_array;

int allocate_map(void){
	bit_array=(int*)malloc(sizeof(unsigned int)*DIM_ARRAY());
	if(bit_array==NULL){
		return -1;
	}
	for(int i=0;i<(DIM_ARRAY());i++){
		bit_array[i]=0;
	}
	return 1;
}

int allocate_pid(void){
	int pid=-1;
	int found=0;
	int cond;
	for(int i=0;i<(BIT_NEEDED()) && !found;i++){
		cond=bit_array[i/INT_BITS()] & (1 << (i%INT_BITS()));//just for readebility
		if(cond==0){
			pid=i;
			found=1;
			bit_array[i/INT_BITS()] |=(1 << (i%INT_BITS()));
		}
	}
	return (pid==-1)? 1:pid+MIN_PID;
}

void release_pid(int pid){
	pid=pid-MIN_PID;
	bit_array[pid/INT_BITS()] &= ~(1<< (pid%INT_BITS())); 
}

int ret_pid(int pos){
	if(pos>BIT_NEEDED()){
		return -1;
	}
	return (bit_array[pos/INT_BITS()] & (1<< (pos%INT_BITS())))!=0;

}
