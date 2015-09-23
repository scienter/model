#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <time.h>
#include <math.h>
#include "constants.h"

float laser(float x,float sigma,float a0);

int main(int argc, char *argv[])
{
   float a0,sigma,density,rangeX,wp,kp,minX,dx,x,a,pot,E,px;
   float *phi;
   int Nx,i;
   char name[100];
   FILE *out;

   if(argc<5)
   {
     printf("show a0 sigma density rangeX Nx\n");
     exit(0);
   }
   
   a0=atof(argv[1]);
   sigma=atof(argv[2]);
   density=atof(argv[3]);
   rangeX=atof(argv[4]);
   Nx=atoi(argv[5]);

   wp=sqrt(density*eCharge*eCharge/eMass/eps0);
   kp=wp/velocityC;
   sigma=sigma*kp;
   minX=-rangeX*kp;

   dx=rangeX*kp/((float)Nx);
   phi=(float *)malloc((Nx+1)*sizeof(float));
   for(i=0; i<=Nx; i++)
     phi[i]=0.0;

   //calculate potential
   for(i=Nx-2; i>=0; i--)
   {
     x=(i+1)*dx+minX;
     a=laser(x,sigma,a0);
     phi[i]=0.5*dx*dx*((1.0+a*a)/(1.0+phi[i+1])/(1.0+phi[i+1])-1.0)-phi[i+2]+2.0*phi[i+1];
   }

   //save laser  
   out=fopen("result","w"); 
   for(i=0; i<Nx; i++)
   {
     x=i*dx+minX;
     a=laser(x,sigma,a0);
     pot=phi[i];
     E=-(phi[i+1]-phi[i])/dx;
     px=0.5*((1.0+a*a)/(1.0+pot)-(1.0+pot));
     fprintf(out,"%g %g %g %g %g\n",x,a,E,-pot,px);
   }
   fclose(out);
   

   free(phi);
   return 0;   
}

float laser(float x,float sigma,float a0)
{
   float result,x0;

   x0=4.0*sigma;
   result=a0*exp(-(x+x0)*(x+x0)/sigma/sigma);
   return result;
}
