#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Rt 6378000.0
#define B0 0.00003
#define m 0.00000000000000000000000000167
#define c 300000000
#define conversion 0.000000000000160217
#define PI 3.14159265

int main(int argc, char **argv){
        double h, tmin,tmax;
        double *x,*y,*z;
        double *xprime,*yprime, *zprime;
    	double *t;
    	double xfunc, yfunc, zfunc;
        double xfuncprime, yfuncprime, zfuncprime;
        double E0,alpha,v0;
    	int j,i,n_points;
    
        h=0.001;
    	tmin=0.0;
    	tmax=100.0;
        n_points=100;
        t=malloc(n_points*sizeof(double));
        x=malloc(n_points*sizeof(double));
        y=malloc(n_points*sizeof(double));
        z=malloc(n_points*sizeof(double));
        xprime=malloc(n_points*sizeof(double));
        yprime=malloc(n_points*sizeof(double));
        zprime=malloc(n_points*sizeof(double));
    
    E0 = atoi(argv[1])*conversion;
    alpha = atoi(argv[2]);
    v0=sqrt(1-(1/(1+(E0/(m*pow(c,2))))));
    
    x[0]=Rt;
    y[0]=0.0;
    z[0]=0.0;
    xprime[0]=0;
    yprime[0]=v0*cos(alpha* PI / 180.0);
    zprime[0]=v0*sin(alpha * PI / 180.0);
    
    printf("%f %f %f \n",E0,m,v0);

}
