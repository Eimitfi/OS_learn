#ifndef _PID_MANAGER_H
#define _PID_MANAGER_H
#include <stdlib.h>
#define MIN_PID 300
#define MAX_PID 302
#define INT_BITS() (sizeof(unsigned int)*8)
#define BIT_NEEDED() (MAX_PID-MIN_PID+1)
#define OFFSET_ARRAY() BIT_NEEDED()%INT_BITS()
#define DIM_ARRAY() (OFFSET_ARRAY()==0)?(BIT_NEEDED()/INT_BITS()):(BIT_NEEDED()/INT_BITS())

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
int ret_pid(int pos);



#endif
