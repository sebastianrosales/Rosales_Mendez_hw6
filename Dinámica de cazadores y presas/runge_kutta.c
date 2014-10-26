

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 20
#define B 1
#define C 30
#define D 1

int main(int argc, char **argv){
    
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
    

    
    h=0.001;
    tmin=0.0;
    tmax=1.0;
    n_points=(tmax-tmin)/h;
    t=malloc(n_points*sizeof(double));
    x=malloc(n_points*sizeof(double));
    y=malloc(n_points*sizeof(double));
    
/* valores de equilibrio son
    x[0]=C/D;
    y[0]=A/B;
*/
    x[0] = atoi(argv[1]);
    y[0] = atoi(argv[2]);
    
    int x0=x[0];
    int y0=y[0];
    
    char bufx[20];
    char bufy[20];
    char nm= x0 -'0';
    char nm2= y0-'0';
    sprintf(bufx, "%d", x0);
    sprintf(bufy, "%d", y0);
    char filename[50], n2[50], n3[50];
    strcpy(filename,  "poblaciones_");
    strcpy(n2,"_");
    strcpy(n3, ".dat");
    
    strcat(filename, bufx);
    strcat(filename, n2);
    strcat(filename, bufy);
    strcat(filename, n3);
    
    FILE* in;
    in = fopen(filename,"w");

    
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
        x[i] = x[i-1] + h*xfunc5;
        y[i] = y[i-1] + h*yfunc5;
    
      //  printf("%f %f \n",h*xfunc5,h*yfunc5);
    fprintf(in, "%f\t%f\t%f \n",t[i],x[i],y[i]);
    }
    
    


}
