#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "mpi.h"

void main(int argc, char *argv[])
{
  int i,final,saveStep;
  float x,t,x0,m,c,gamma,p,p0,dt,density,energy0,field,xold,e;
  FILE *out;
  char name[100];
  float momentum(float x,float t,float p0,float n);
  float Efield(float x,float n);
  
  if(argc<5)
  {
    printf("solution [final] [saveStep] [energy0] [dt] [density]\n");
    exit(0);
  }
  final=atoi(argv[1]);
  saveStep=atoi(argv[2]);
  energy0=atof(argv[3]);
  dt=atof(argv[4]);
  density=atof(argv[5]);


  x0=50e-9;
  m=9.11e-31;
  c=3e8;
  e=1.602e-19;
  
//  p0=sqrt(energy0*2.0*m*e);
  gamma=energy0/0.511e6+1.0;
  p0=sqrt(gamma*gamma-1.0)*m*c;

  out=fopen("Ex","w");
  for(x=x0; x<=2e-5; x+=1e-7)
  {
    field=Efield(x,density);
    fprintf(out,"%g %g\n",x,field);
  }
  fclose(out);


  x=xold=x0;
  for(i=0; i<=final; i++)
  {
    t=dt*i;
    p=momentum(0.5*(x+xold),t+0.5*dt,p0,density);
    gamma=sqrt(1.0+p*p/m/m/c/c);
    xold=x;
    x=xold+p/m/gamma*dt;
    printf("%g %g %g\n",x,p,gamma);
  }
}

float momentum(float x,float t,float p0,float n)
{
  float e,eps0,A,result;

  e=1.601e-19;
  eps0=8.85e-12;
  A=50e-9*50e-9*3.14;
  
  result=p0+0.5/3.14/eps0*e*n*A*t/x;

  return result;
}

float Efield(float x,float n)
{
  float e,eps0,A,result;

  e=1.601e-19;
  eps0=8.85e-12;
  A=50e-9*50e-9*3.14;
  result=0.5/3.14/eps0*e*n*A/x;

  return result;
}  
