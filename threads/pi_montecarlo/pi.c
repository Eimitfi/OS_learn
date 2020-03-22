#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

/*** data structures ***/
typedef enum {false,true} Boolean;

typedef struct{
	double x;
	double y;
} point;
/*** data ***/
int num_inside;
int total;
/*** functions declarations ***/
void * throw_points(void * param);
point generate_point(void);
Boolean is_inside(point punct);

int main(int argc,char ** argv){
	srand(time(NULL));
	if(argc!=2){
		fprintf(stderr,"insert the accuracy i.e. number of points\n");
		return 1;
	}
	double pi;
	int num_points=atoi(argv[1]);
	num_inside=0;
	total=0;
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,throw_points,(void*)&num_points);
	pthread_join(tid,NULL);
	pi=((double)num_inside*4)/total;
	printf("the approximation with %d points is: %f\n",num_points,pi);
}

void * throw_points(void * param){
	int num_points=*((int*)param);
	for(;total<num_points;total++){
		num_inside=(is_inside(generate_point()))?num_inside+1:num_inside;
	}
	pthread_exit(0);
}

point generate_point(void){
	point punto;
	punto.x=((double)rand()*2)/RAND_MAX-1;
	punto.y=((double)rand()*2)/RAND_MAX-1;
	return punto;
}

Boolean is_inside(point punct){
	return (sqrt(punct.x*punct.x+punct.y*punct.y)<=1)?true:false;
}
