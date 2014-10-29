#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Rt 6378137
#define B0 0.00003
#define m 0.0000000000000000000000000016726
#define c 300000000
#define cc 90000000000000000
#define PI 3.14159265
#define e 0.000000000000000000160217

double func1(double x,double y, double z,double xprime, double yprime,double zprime, double v0);
double func2(double x,double y, double z,double xprime, double yprime,double zprime, double v0);
double func3(double x,double y, double z,double xprime, double yprime,double zprime, double v0);
double funcprime1(double x,double y, double z,double xprime, double yprime,double zprime);
double funcprime2(double x,double y, double z,double xprime, double yprime,double zprime);
double funcprime3(double x,double y, double z,double xprime, double yprime,double zprime);

int main(int argc, char **argv){
    
    double h, tmin,tmax;
    double *x;
    double *y;
    double *z;
    double *xprime;
    double *yprime;
    double *zprime;
    double *t;
    double x1, y1,z1, t1;
    double x2, y2,z2, t2;
    double x3, y3,z3, t3;
    double xprime1, yprime1,zprime1;
    double xprime2, yprime2,zprime2;
    double xprime3, yprime3,zprime3;
    double kx1, ky1, kz1;
    double kx2, ky2, kz2;
    double kx3, ky3, kz3;
    double kx4, ky4, kz4;
    double kx5, ky5, kz5;
    double kxprime1, kyprime1, kzprime1;
    double kxprime2, kyprime2, kzprime2;
    double kxprime3, kyprime3, kzprime3;
    double kxprime4, kyprime4, kzprime4;
    double kxprime5, kyprime5, kzprime5;
    double E0 ,E0j,alpha,v0, gamma,v1;
  
    int i,n_points;
    

    
    h=0.00005;
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
    E0 = atof(argv[1]);
    E0j = E0*e*1000000;
    alpha = atof(argv[2]);
    v0=c*sqrt(1-(1/pow((1+E0j/(m*cc)),2)));
    //v0= c/sqrt(1+(m*cc)/E0j);
    //v0=c*sqrt(1-(1/pow((1+E0j),2)));
    gamma =1.0/sqrt(1 - pow(v0,2)/cc);
  
    //abre el archivo para escribir
    
    FILE *in;
    char filename[100000];
    sprintf(filename, "trayectoria_%d_%d.dat", (int)E0 ,(int)alpha);
    in = fopen(filename,"w");
   
    //condiciones iniciales
    t[0]=0.0;
    x[0]=2*Rt;
    y[0]=0.0;
    z[0]=0.0;
    xprime[0]=0;
    yprime[0]=v0*sin(alpha* PI / 180.0);
    zprime[0]=v0*cos(alpha * PI / 180.0);
    
    fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",x[0],y[0],z[0],xprime[0],yprime[0],zprime[0],v0);
   
    
//rungekutteira

    
    for(i=1;i<n_points;i++){
        
      //k es la aceleración
      kx1=func1(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1],v0);
      ky1=func2(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1],v0);
      kz1=func3(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1],v0);
      //kprime es la velocidad 
      kxprime1=funcprime1(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1]);
      kyprime1=funcprime2(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1]);
      kzprime1=funcprime3(x[i-1],y[i-1],z[i-1],xprime[i-1],yprime[i-1],zprime[i-1]);
        
  
//primer paso
        
        t1=t[i-1]+h;
        
        x1=x[i-1]+h*kxprime1/2.0;
        xprime1=xprime[i-1]+h*kx1/2.0;
        kxprime2=funcprime1(x1,y1,z1,xprime1,yprime1,zprime1);
        
        
        y1=y[i-1]+h*kyprime1/2.0;
        yprime1=yprime[i-1]+h*ky1/2.0;
        kyprime2=funcprime2(x1,y1,z1,xprime1,yprime1,zprime1);
        
        
        
        z1=z[i-1]+h*kzprime1/2.0;
        zprime1=zprime[i-1]+h*kz1/2.0;
        kzprime2=funcprime3(x1,y1,z1,xprime1,yprime1,zprime1);
       
        
        kx2=func1(x1,y1,z1,xprime1,yprime1,zprime1,v0);
        ky2=func2(x1,y1,z1,xprime1,yprime1,zprime1,v0);
        kz2=func3(x1,y1,z1,xprime1,yprime1,zprime1,v0);
      
//segundo paso 
        
        
        t2=t[i-1]+h;
        
        x2=x[i-1]+h*kxprime2/2.0;
        xprime2=xprime[i-1]+h*kx2/2.0;
        kxprime3=funcprime1(x2,y2,z2,xprime2,yprime2,zprime2);
        
        
        y2=y[i-1]+h*kyprime2/2.0;
        yprime2=yprime[i-1]+h*ky2/2.0;
        kyprime3=funcprime2(x2,y2,z2,xprime2,yprime2,zprime2);
       
        
        z2=z[i-1]+h*kzprime2/2.0;
        zprime2=zprime[i-1]+h*kz2/2.0;
        kzprime3=funcprime3(x2,y2,z2,xprime2,yprime2,zprime2);
       
        kx3=func1(x2,y2,z2,xprime2,yprime2,zprime2,v0);
        ky3=func2(x2,y2,z2,xprime2,yprime2,zprime2,v0);
        kz3=func3(x1,y1,z1,xprime1,yprime1,zprime1,v0);

        
//tercer paso
        
        t3=t[i-1]+h;
        
        x3=x[i-1]+h*kxprime3/2.0;
        xprime3=xprime[i-1]+h*kx3/2.0;
        kxprime4=funcprime1(x3,y3,z3,xprime3,yprime3,zprime3);
        
        
        y3=y[i-1]+h*kyprime3/2.0;
        yprime3=yprime[i-1]+h*ky3/2.0;
        kyprime4=funcprime2(x3,y3,z3,xprime3,yprime3,zprime3);
        
        
        z3=z[i-1]+h*kzprime3/2.0;
        zprime3=zprime[i-1]+h*kz3/2.0;
        kzprime4=funcprime3(x3,y3,z3,xprime3,yprime3,zprime3);
        
        kx4=func1(x3,y3,z3,xprime3,yprime3,zprime3,v0);
        ky4=func2(x3,y3,z3,xprime3,yprime3,zprime3,v0);
        kz4=func3(x3,y3,z3,xprime3,yprime3,zprime3,v0);
        
//cuarto paso
        

        kx5=(1.0/6.0)*(kx1 + 2.0*kx2 + 2.0*kx3 + kx4);
        ky5=(1.0/6.0)*(ky1 + 2.0*ky2 + 2.0*ky3 + ky4);
        kz5=(1.0/6.0)*(kz1 + 2.0*kz2 + 2.0*kz3 + kz4);
        kxprime5=(1.0/6.0)*(kxprime1 + 2.0*kxprime2 + 2.0*kxprime3 + kxprime4);
        kyprime5=(1.0/6.0)*(kyprime1 + 2.0*kyprime2 + 2.0*kyprime3 + kyprime4);
        kzprime5=(1.0/6.0)*(kzprime1 + 2.0*kzprime2 + 2.0*kzprime3 + kzprime4);


        t[i]=t[i-1]+h;
        xprime[i]=xprime[i-1]+h*kx5;
        yprime[i]=yprime[i-1]+h*ky5;
        zprime[i]=zprime[i-1]+h*kz5;
        x[i]=x[i-1]+h*kxprime5;
        y[i]=y[i-1]+h*kyprime5;
        z[i]=z[i-1]+h*kzprime5;
        
        v1=sqrt(pow(xprime[i],2)+pow(yprime[i],2)+pow(zprime[i],2));
        
        
    //printf( "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",xfunc5,yfunc5,zfunc5,xfuncprime5,yfuncprime5,zfuncprime5,v1);
    fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",x[i],y[i],z[i],xprime[i],yprime[i],zprime[i],v1);
    }
    
    
    return 0;

}




double func1(double x,double y, double z,double xprime, double yprime,double zprime,double v0){

    double xfunc1;
    double Bx,By,Bz,r,k,v1,gamma;

    
    r=pow(x,2)+pow(y,2)+pow(z,2);
    k=-e*B0*pow(Rt,3)/pow(r,5.0/2.0);
    
    Bx=(3*y*x);
    By=(3*y*z);
    Bz=(2*pow(z,2)-pow(y,2)-pow(x,2));
    
    v1=pow(xprime,2)+pow(yprime,2)+pow(zprime,2);
    gamma =1.0/sqrt(1 - v1/cc);
    
    
    xfunc1=k*(Bz*yprime-By*zprime)/(m*gamma);
    
    return xfunc1;
    
    
}


double func2(double x,double y, double z,double xprime, double yprime,double zprime,double v0){
    
    double yfunc1;
    double Bx,By,Bz,r,k,v1,gamma;
    
    
    r=pow(x,2)+pow(y,2)+pow(z,2);
    k=-e*B0*pow(Rt,3)/pow(r,5.0/2.0);
    
    Bx=(3*y*x);
    By=(3*y*z);
    Bz=(2*pow(z,2)-pow(y,2)-pow(x,2));
    
    v1=pow(xprime,2)+pow(yprime,2)+pow(zprime,2);
    gamma =1.0/sqrt(1 - v1/cc);
    
    
    yfunc1=k*(Bx*zprime-Bz*xprime)/(m*gamma);
    
    return yfunc1;
    
}

double func3(double x,double y, double z,double xprime, double yprime,double zprime, double v0){
    
    double zfunc1;
    double Bx,By,Bz,r,k,v1,gamma;
    
    
    r=pow(x,2)+pow(y,2)+pow(z,2);
    k=-e*B0*pow(Rt,3)/pow(r,5.0/2.0);
    
    Bx=(3*y*x);
    By=(3*y*z);
    Bz=(2*pow(z,2)-pow(y,2)-pow(x,2));
    
    v1=pow(xprime,2)+pow(yprime,2)+pow(zprime,2);
    gamma =1.0/sqrt(1 - v1/cc);
    
    
    zfunc1=k*(By*xprime-Bx*yprime)/(m*gamma);
    
    return zfunc1;
    
}

double funcprime1(double x,double y, double z,double xprime, double yprime,double zprime){

    return xprime;

}
double funcprime2(double x,double y, double z,double xprime, double yprime,double zprime){
    
    return yprime;

}
double funcprime3(double x,double y, double z,double xprime, double yprime,double zprime){

    return zprime;
    
}
