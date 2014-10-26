#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
	double h, tmin,tmax;
	double *x,*y,*z;
    	double *t;
    	double x1, y1, t1;
    	double x2, y2, t2;
    	double x3, y3, t3;
    	double xfunc1, yfunc1;
    	double xfunc2, yfunc2;
    	double xfunc3, yfunc3;
    	double xfunc4, yfunc4;
    	double xfunc5, yfunc5;
    	int j,i,n_points;
	h=0.001;
    	tmin=0.0;
    	tmax=1.0;
	n_points=(tmax-tmin)/h;
 	t=malloc(n_points*sizeof(double));
   	x=malloc(n_points*sizeof(double));
   	y=malloc(n_points*sizeof(double));
	z=malloc(n_points*sizeof(double));
}
