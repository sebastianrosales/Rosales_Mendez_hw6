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
#define e 0.000000000000000000160217

int main(int argc, char **argv){
        double h, tmin,tmax;
        double *x,*y,*z;
        double *xprime,*yprime, *zprime;
    	double *t;
    	double xfunc, yfunc, zfunc;
        double xfuncprime, yfuncprime, zfuncprime;
        double E0 ,E0j,alpha,v0, gamma;
        double Bx,By,Bz,r,k;
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
    
    E0 = atoi(argv[1]);
    E0j = E0*conversion;
    alpha = atoi(argv[2]);
    v0=sqrt(1-(1/(1+pow((E0/(m*pow(c,2))),2))));
    gamma =1+(E0/(m*pow(c,2)));
            
    k=-(e*B0*pow(Rt,3))/(m*gamma);
        
    x[0]=Rt;
    y[0]=0.0;
    z[0]=0.0;
    xprime[0]=0;
    yprime[0]=v0*cos(alpha* PI / 180.0);
    zprime[0]=v0*sin(alpha * PI / 180.0);
   
    r=pow(x[0],2)+pow(y[0],2)+pow(z[0],2);
    
    Bx=(3*y[0]*x[0])/pow(r,5);
    By=(3*y[0]*z[0])/pow(r,5);
    Bz=k*(2*pow(z[0],2)-pow(y[0],2)-pow(x[0],2))/pow(r,5);
              

    xfunc=Bz*yprime[0]-By*zprime[0];
    yfunc=Bx*zprime[0]-Bz*xprime[0];
    zfunc=By*xprime[0]-Bx*yprime[0];
    xfuncprime=0;
    yfuncprime=0;
    zfuncprime=0;
    
    
    char bufE[20];
    char bufa[20];
    char nm= E0-'0';
    char nm2= alpha - '0';
    sprintf(bufE, "%f", E0);
    sprintf(bufa, "%f", alpha);
    char filename[50], n2[50], n3[50];
    strcpy(filename,  "trayectoria_");
    strcpy(n2,"_");
    strcpy(n3, ".dat");
    
    strcat(filename, bufE);
    strcat(filename, n2);
    strcat(filename, bufa);
    strcat(filename, n3);
    
    FILE* in;
    in = fopen(filename,"w");
    
    for(i=1;i<n_points;i++){
        
        
        
        
    }
    

 //   printf("%f %f %f \n",E0,m,v0);

}
