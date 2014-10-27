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
        double Bx,By,Bz,r,k,r2;
    	int j,i,n_points;
    
        h=1;
    	tmin=0.0;
    	tmax=100.0;
        n_points=(tmax-tmin)/h;
        t=malloc(n_points*sizeof(double));
        x=malloc(n_points*sizeof(double));
        y=malloc(n_points*sizeof(double));
        z=malloc(n_points*sizeof(double));
        xprime=malloc(n_points*sizeof(double));
        yprime=malloc(n_points*sizeof(double));
        zprime=malloc(n_points*sizeof(double));
   
//constantes
    E0 = atoi(argv[1]);
    E0j = E0*conversion;
    alpha = atoi(argv[2]);
    v0=c*sqrt(1-(1/pow(1+E0j/(m*pow(c,2)),2)));
    gamma =1+(E0/(m*pow(c,2)));
    k=-(e*B0*pow(Rt,3))/(m*gamma);
    printf("%f \n",v0);
    
//abre archivo para escribir
    
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

//condiciones iniciales
    t[0]=0.0;
    x[0]=2*Rt;
    y[0]=0.0;
    z[0]=0.0;
    xprime[0]=0;
    yprime[0]=v0*cos(alpha* PI / 180.0);
    zprime[0]=v0*sin(alpha * PI / 180.0);
    
  fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t[0],x[0],y[0],z[0],xprime[0],yprime[0],zprime[0]);
   
//primer paso de euler
    
    r=pow(x[0],2)+pow(y[0],2)+pow(z[0],2);
    r2=pow(r,0.5);
    
    Bx=k*(3*y[0]*x[0])/pow(r2,5);
    By=k*(3*y[0]*z[0])/pow(r2,5);
    Bz=k*(2*pow(z[0],2)-pow(y[0],2)-pow(x[0],2))/pow(r2,5);
              

    xfunc=Bz*yprime[0]-By*zprime[0];
    yfunc=Bx*zprime[0]-Bz*xprime[0];
    zfunc=By*xprime[0]-Bx*yprime[0];
    xfuncprime=xprime[0];
    yfuncprime=yprime[0];
    zfuncprime=zprime[0];
    
    t[1]=t[0]+h;
    xprime[1]=xprime[0]+h*xfunc;
    yprime[1]=yprime[0]+h*yfunc;
    zprime[1]=zprime[0]+h*zfunc;
    x[1]=x[0]+h*xfuncprime;
    y[1]=y[0]+h*yfuncprime;
    z[1]=z[0]+h*zfuncprime;
    
    
    fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t[1],x[1],y[1],z[1],xprime[1],yprime[1],zprime[1]);
    
    //leapfrog
    
    for(i=1;i<(n_points-1);i++){
        
        r=pow(x[i-1],2)+pow(y[i-1],2)+pow(z[i-1],2);
        r2=pow(r,0.5);
        
        Bx=k*(3*y[i-1]*x[i-1])/pow(r2,5);
        By=k*(3*y[i-1]*z[i-1])/pow(r2,5);
        Bz=k*(2*pow(z[i-1],2)-pow(y[i-1],2)-pow(x[i-1],2))/pow(r2,5);
        
        
        xfunc=Bz*yprime[i-1]-By*zprime[i-1];
        yfunc=Bx*zprime[i-1]-Bz*xprime[i-1];
        zfunc=By*xprime[i-1]-Bx*yprime[i-1];
        xfuncprime=xprime[i-1];
        yfuncprime=yprime[i-1];
        zfuncprime=zprime[i-1];
        
        t[i+1]=t[i-1]+2*h;
        xprime[i+1]=xprime[i-1]+2*h*xfunc;
        yprime[i+1]=yprime[i-1]+2*h*yfunc;
        zprime[i+1]=zprime[i-1]+2*h*zfunc;
        x[i+1]=x[i-1]+2*h*xfuncprime;
        y[i+1]=y[i-1]+2*h*yfuncprime;
        z[i+1]=z[i-1]+2*h*zfuncprime;
        
        
        
         fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t[i+1],x[i+1],y[i+1],z[i+1],xprime[i+1],yprime[i+1],zprime[i+1]);
    }
    

    
 //   printf("%f %f %f \n",E0,m,v0);

}
