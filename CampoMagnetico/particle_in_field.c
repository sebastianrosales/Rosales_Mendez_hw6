#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Rt 6378137
#define B0 3E-5
#define m 1.6726E-27
#define c 299792458
#define cc 8.9875518E16
#define PI 3.14159265
#define e 1.60217E-19

double funcacel1(double x,double y, double z,double xprime, double yprime,double zprime, double gamma);
double funcacel2(double x,double y, double z,double xprime, double yprime,double zprime, double gamma);
double funcacel3(double x,double y, double z,double xprime, double yprime,double zprime, double gamma);


int main(int argc, char **argv){
    
    double h, tmin,tmax;
    double x_old;
    double y_old;
    double z_old;
    double xprime_old;
    double yprime_old;
    double zprime_old;
    double x_new;
    double y_new;
    double z_new;
    double xprime_new;
    double yprime_new;
    double zprime_new;
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
    double E0 ,E0j,alpha,v0, gamma,v1;
  
    int i,n_points;
    
  
    //constantes
    E0 = atof(argv[1]);
    alpha = atof(argv[2]);
    E0j = E0*e*1000000;
    gamma =1+E0j/(m*cc);
    v0=c*sqrt(1-(1/pow(gamma,2)));
   
    
    h=(2*PI*gamma*m/(e*B0))/50;
    tmin=0.0;
    tmax=100.0;
    n_points=(tmax-tmin)/h;
    
    //abre el archivo para escribir
    
    FILE *in;
    char filename[100000];
    sprintf(filename, "trayectoria_%d_%d.dat", (int)E0 ,(int)alpha);
    in = fopen(filename,"w");
   
    //condiciones iniciales
    x_old=2*Rt;
    y_old=0.0;
    z_old=0.0;
    xprime_old=0;
    yprime_old=v0*sin(alpha* PI / 180.0);
    zprime_old=v0*cos(alpha * PI / 180.0);
    
    fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",x_old,y_old,z_old,xprime_old,yprime_old,zprime_old,v0);
   
    
//rungekutteira

    
    for(i=1;i<n_points;i++){
    
      kx1=funcacel1(x_old,y_old,z_old,xprime_old,yprime_old,zprime_old,gamma);
      ky1=funcacel2(x_old,y_old,z_old,xprime_old,yprime_old,zprime_old,gamma);
      kz1=funcacel3(x_old,y_old,z_old,xprime_old,yprime_old,zprime_old,gamma);
      
  
//primer paso
        
        
        x1=x_old+h*xprime_old/2.0;
        y1=y_old+h*yprime_old/2.0;
        z1=z_old+h*zprime_old/2.0;
        xprime1=xprime_old+h*kx1/2.0;
        yprime1=yprime_old+h*ky1/2.0;
        zprime1=zprime_old+h*kz1/2.0;
    
        kx2=funcacel1(x1,y1,z1,xprime1,yprime1,zprime1,gamma);
        ky2=funcacel2(x1,y1,z1,xprime1,yprime1,zprime1,gamma);
        kz2=funcacel3(x1,y1,z1,xprime1,yprime1,zprime1,gamma);
      
//segundo paso 
        
    
        x2=x_old+h*xprime1/2.0;
        y2=y_old+h*yprime1/2.0;
        z2=z_old+h*zprime1/2.0;
        xprime2=xprime_old+h*kx2/2.0;
        yprime2=yprime_old+h*ky2/2.0;
        zprime2=zprime_old+h*kz2/2.0;
        
        kx3=funcacel1(x2,y2,z2,xprime2,yprime2,zprime2,gamma);
        ky3=funcacel2(x2,y2,z2,xprime2,yprime2,zprime2,gamma);
        kz3=funcacel3(x2,y2,z2,xprime2,yprime2,zprime2,gamma);

        
//tercer paso
        
        
        x3=x_old+h*xprime2;
        y3=y_old+h*yprime2;
        z3=z_old+h*zprime2;
        xprime3=xprime_old+h*kx3;
        yprime3=yprime_old+h*ky3;
        zprime3=zprime_old+h*kz3;
        
        kx4=funcacel1(x3,y3,z3,xprime3,yprime3,zprime3,gamma);
        ky4=funcacel2(x3,y3,z3,xprime3,yprime3,zprime3,gamma);
        kz4=funcacel3(x3,y3,z3,xprime3,yprime3,zprime3,gamma);
        
//cuarto paso
        

        kx5=(1.0/6.0)*(kx1 + 2.0*kx2 + 2.0*kx3 + kx4);
        ky5=(1.0/6.0)*(ky1 + 2.0*ky2 + 2.0*ky3 + ky4);
        kz5=(1.0/6.0)*(kz1 + 2.0*kz2 + 2.0*kz3 + kz4);
    

        xprime_new=xprime_old+h*kx5;
        yprime_new=yprime_old+h*ky5;
        zprime_new=zprime_old+h*kz5;
        x_new=x_old+h*(xprime_new+xprime_old)/2;
        y_new=y_old+h*(yprime_new+yprime_old)/2;
        z_new=z_old+h*(zprime_new+zprime_old)/2;
        
        v1=sqrt(pow(xprime_new,2)+pow(yprime_new,2)+pow(zprime_new,2));
        
        xprime_old=xprime_new;
        yprime_old=yprime_new;
        zprime_old=zprime_new;
        x_old=x_new;
        y_old=y_new;
        z_old=z_new;

        
        
    fprintf(in, "%f\t%f\t%f\t%f\t%f\t%f\t%f \n",x_new,y_new,z_new,xprime_new,yprime_new,zprime_new,v1);
    }
    
    
    return 0;

}




double funcacel1(double x,double y, double z,double xprime, double yprime,double zprime,double gamma){

    double r;
    r=pow(x,2)+pow(y,2)+pow(z,2);
    return e*(-B0*(pow(Rt,3)))*(yprime*(2*z*z-x*x-y*y)-zprime*(3*y*z))/(m*gamma*pow(r,5.0/2.0));
    

    
}

double funcacel2(double x,double y, double z,double xprime, double yprime,double zprime, double gamma){
    
    double r;
    r=pow(x,2)+pow(y,2)+pow(z,2);
    return e*(-B0*(pow(Rt,3)))*(zprime*(3*x*z)-xprime*(2*z*z-x*x-y*y))/(m*gamma*pow(r,5.0/2.0));
    
}


double funcacel3(double x,double y, double z,double xprime, double yprime,double zprime,double gamma){
    
    double r;
    r=pow(x,2)+pow(y,2)+pow(z,2);
    return e*(-B0*(pow(Rt,3)))*(xprime*(3*y*z)-yprime*(3*x*z))/(m*gamma*pow(r,5.0/2.0));
    
}
