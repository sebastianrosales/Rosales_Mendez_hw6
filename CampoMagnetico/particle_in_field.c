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
#define k -0.018308
double p2(x){
return pow(x,2);
}
double f1(double x, double y, double z, double vx, double vy, double vz){
double r,r2;
r2=p2(x)+p2(y)+p2(z);
r=pow(r2,0.5);
return k/pow(r,5)*((r2-3*p2(z))*vy-3*y*z*vz);
}
double f2(double x, double y, double z, double vx, double vy, double vz){
double r,r2;
r2=p2(x)+p2(y)+p2(z);
r=pow(r2,0.5);
return k/pow(r,5)*(3*x*y*vz-(r2-3*p2(z))*vx);
}
double f3(double x, double y, double z, double vx, double vy, double vz){
double r,r2;
r2=p2(x)+p2(y)+p2(z);
r=pow(r2,0.5);
return k/pow(r,5)*(3*y*z*vx-3*x*y*vz);
}
int main(int argc, char **argv){
        double h, tmin,tmax;
        double *x,*y,*z;
        double *xprime,*yprime, *zprime;
    	double *t;
    	double xfunc, yfunc, zfunc;
        double xfuncprime, yfuncprime, zfuncprime;
        double E0 ,E0j,alpha,v0, gamma;
        double Bx,By,Bz,r;
    	int j,i,n_points;
    
        h=0.001;
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
    v0=sqrt(1-(1/(1+pow((E0/(m*pow(c,2))),2))));
    gamma =1+(E0/(m*pow(c,2)));
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
    zprime[0]=v0*sin(alpha* PI / 180.0);
    
    fprintf(in, "%f\t%f\t%f\t%f \n",t[0],x[0],y[0],z[0]);

//Hasta acá estoy de acuerdo con lo que tenía Ud. Solo redefiní n_points. 
   
//primer paso de euler
              

    xfunc=f1(x[0],y[0],z[0],xprime[0],yprime[0],zprime[0]);
    yfunc=f2(x[0],y[0],z[0],xprime[0],yprime[0],zprime[0]);
    zfunc=f3(x[0],y[0],z[0],xprime[0],yprime[0],zprime[0]);
/**Qué es eso?
    xfuncprime=xprime[0];
    yfuncprime=yprime[0];
    zfuncprime=zprime[0];
**/    
    t[1]=t[0]+h;
    x[1]=x[0]+h*xfuncprime;
    y[1]=y[0]+h*yfuncprime;
    z[1]=z[0]+h*zfuncprime;
/**  No entiendo. Lo que le entiendo es esto: 
    velocidad(1)=velocidad(0)+(h)*velocidad(0)
    las unidades le quedan mal 
    m/s=m/s+(s*m/s)  
    xprime[1]=xprime[0]+h*xfuncprime;
    yprime[1]=yprime[0]+h*yfuncprime;
    zprime[1]=zprime[0]+h*zfuncprime;

    Pille yo haría esto: 
**/
    xprime[1]=xprime[0]+h*xfunc;
    yprime[1]=yprime[0]+h*yfunc;
    zprime[1]=zprime[0]+h*zfuncprime;
    t[1]=t[0]+h;
    fprintf(in, "%f\t%f\t%f\t%f \n",t[1],x[1],y[1],z[1]);
    
    //leapfrog
    
    for(i=1;i<(n_points-1);i++){

	//Defino las aceleraciones
	xfunc=f1(x[i],y[i],z[i],xprime[i],yprime[i],zprime[i]);
	yfunc=f2(x[i],y[i],z[i],xprime[i],yprime[i],zprime[i]);
	zfunc=f3(x[i],y[i],z[i],xprime[i],yprime[i],zprime[i]);
	//Avanzo el tiempo
	t[i+1]=t[i]+h;
	//Avanzo las posiciones
	x[i+1]=2*x[i]+pow(h,2)*xfunc-x[i-1];
	y[i+1]=2*y[i]+pow(h,2)*yfunc-y[i-1];
	z[i+1]=2*z[i]+pow(h,2)*zfunc-z[i-1];
	//Avanzo las velocidades
	xprime[i+1]=xprime[i-1]+2*h*xfunc; 
	yprime[i+1]=yprime[i-1]+2*h*yfunc; 
	zprime[i+1]=zprime[i-1]+2*h*zfunc; 

/***
        r=pow(x[i-1],2)+pow(y[i-1],2)+pow(z[i-1],2);
        
        Bx=(3*y[i-1]*x[i-1])/pow(r,5);
        By=(3*y[i-1]*z[i-1])/pow(r,5);
        Bz=k*(2*pow(z[i-1],2)-pow(y[i-1],2)-pow(x[i-1],2))/pow(r,5);
        
        
        xfunc=Bz*yprime[i-1]-By*zprime[i-1];
        yfunc=Bx*zprime[i-1]-Bz*xprime[i-1];
        zfunc=By*xprime[i-1]-Bx*yprime[i-1];
        xfuncprime=xprime[i-1];
        yfuncprime=yprime[i-1];
        zfuncprime=zprime[i-1];
        
        t[i+1]=t[i-1]+2*h;
        x[i+1]=x[i-1]+2*h*xfuncprime;
        y[i+1]=y[i-1]+2*h*yfuncprime;
        z[i+1]=z[i-1]+2*h*zfuncprime;
        xprime[i+1]=xprime[i-1]+2*h*xfuncprime;
        yprime[i+1]=yprime[i-1]+2*h*yfuncprime;
        zprime[i+1]=zprime[i-1]+2*h*zfuncprime;
**/        
        
         fprintf(in, "%f\t%f\t%f\t%f \n",t[i+1],x[i+1],y[i+1],z[i+1]);
    }
    

    
 //   printf("%f %f %f \n",E0,m,v0);

}
