#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <time.h>
#include <math.h>
#include "constants.h"

float laser(float x,float sigma,float a0);
float updatePx(float k0,float alpha,float r0,float x0,float x,float t);

int main(int argc, char *argv[])
{
   float a0,sigma,density,rangeX,wp,kp,minX,dx,x,a,pot,E,px;
   float r0,n_n,k0,alpha,gamma,t,dt,f,x0,Enano; 
   float *phi;
   int Nx,i,maxStep;
   char name[100];
   FILE *out;

   if(argc<10)
   {
     printf("show a0 sigma density rangeX Nx finalTime r0 n_n k0 nanoX0\n");
     exit(0);
   }
   
   a0=atof(argv[1]);
   sigma=atof(argv[2]);
   density=atof(argv[3]);
   rangeX=atof(argv[4]);
   Nx=atoi(argv[5]);
   maxStep=atoi(argv[6]);
   r0=atof(argv[7]);
   n_n=atof(argv[8]);
   k0=atof(argv[9]);
   x0=atof(argv[10]);

   wp=sqrt(density*eCharge*eCharge/eMass/eps0);
   kp=wp/velocityC;
   sigma=sigma*kp;
   minX=-rangeX*kp;
   r0=r0*kp;
   alpha=0.5/pi*n_n/density*pi*r0*r0;

   dx=rangeX*kp/((float)Nx);
   phi=(float *)malloc((Nx+1)*sizeof(float));
   dt=r0*0.1;
   for(i=0; i<=Nx; i++)
   {
     phi[i]=0.0;
   }

   //calculate potential
   for(i=Nx-2; i>=0; i--)
   {
     x=(i+1)*dx+minX;
     a=laser(x,sigma,a0);
     phi[i]=0.5*dx*dx*((1.0+a*a)/(1.0+phi[i+1])/(1.0+phi[i+1])-1.0)-phi[i+2]+2.0*phi[i+1];
   }

   //calculate Px
   sprintf(name,"px%g",x0);
   out=fopen(name,"w");
   px=x=0.0;
   for(i=0; i<=maxStep; i++)
   { 
     gamma=sqrt(1.0+px);
     x+=px/gamma*dt;
     t=i*dt+0.5*dt;
     f=updatePx(k0,alpha,r0,x0,x,t);
     px+=f*dt;
     fprintf(out,"%g %g\n",x,px);
   }
   fclose(out);

   //save laser  
   out=fopen("result","w"); 
   for(i=0; i<Nx; i++)
   {
     x=i*dx+minX;
     a=laser(x,sigma,a0);
     pot=phi[i];
     E=-(phi[i+1]-phi[i])/dx;
     Enano=-alpha/(r0-(x-x0));
     if(x>=x0-r0)  Enano=0.0;
     E=E+Enano;
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

float updatePx(float k0,float alpha,float r0,float x0,float x,float t)
{
  float result;

  result=-0.5*k0*(x+x0-t)+alpha/(r0-x);
  return result;
}
