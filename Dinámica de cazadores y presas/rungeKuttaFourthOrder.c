

#include <stdio.h>
#include <stdlib.h>
#define A 20
#define B 1
#define C 30
#define D 1

int main(void){
    
    double h, tmin,tmax;
    double *x;
    double *y;
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
    

    
    h=0.01;
    tmin=0.0;
    tmax=1.0;
    n_points=(tmax-tmin)/h;
    t=malloc(n_points*sizeof(double));
    x=malloc(n_points*sizeof(double));
    y=malloc(n_points*sizeof(double));
    z=malloc(n_points*sizeof(double));
    

    x[0]=C/D;
    y[0]=A/B;

    
    for(i=1;i<n_points;i++){
        
        xfunc1=A*x[i-1]-B*x[i-1]*y[i-1];
        yfunc1=-C*y[i-1]+D*x[i-1]*y[i-1];

//primer paso
        t1=t[i-1]+h/2.0;
        x1=x[i-1]+(h/2.0)*xfunc1;
        y1=y[i-1]+(h/2.0)*yfunc1;
        
        xfunc2=A*x1-B*x1*y1;
        yfunc2=-C*y1+D*x1*y1;
       
//segundo paso 
        
        t2=t[i-1]+h/2.0;
        x2=x[i-1]+(h/2.0)*xfunc2;
        y2=y[i-1]+(h/2.0)*yfunc2;
        
        xfunc3=A*x2-B*x2*y2;
        yfunc3=-C*y2+D*x2*y2;

        
//tercer paso
        t3=t[i-1]+h;
        x3=x[i-1]+(h)*xfunc3;
        y3=y[i-1]+(h)*yfunc3;
        
        xfunc4=A*x3-B*x3*y3;
        yfunc4=-C*y3+D*x3*y3;

        
//cuarto paso
        

        xfunc5=(1.0/6.0)*(xfunc1 + 2.0*xfunc2 + 2.0*xfunc3 + xfunc4);
        yfunc5=(1.0/6.0)*(yfunc1 + 2.0*yfunc2 + 2.0*yfunc3 + yfunc4);


        t[i] = t[i-1] + h;
        x[i] = x[i-1] + h * xfunc5;
        y[i] = y[i-1] + h * xfunc5;
    
    }
    
    FILE *in;
    char filename[100]="poblaciones_";
    
    
    
    in =fopen(filename,"w");
    if(!in){
        printf("problems opening the file %s\n", filename);
        exit(1);
        
    }
    for(i=1;i<n_points;i++){
        
    fprintf(in, "%f\t%f\t%f \n",t[i],x[i],y[i] );
        
    
    }

}
