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
    printf("solution [final] [x0] [energy0] [dt] [density]\n");
    exit(0);
  }
  final=atoi(argv[1]);
  x0=atof(argv[2]);
  energy0=atof(argv[3]);
  dt=atof(argv[4]);
  density=atof(argv[5]);

  m=9.11e-31;
  c=3e8;
  e=1.602e-19;
  
//  p0=sqrt(energy0*2.0*m*e);
  energy0=energy0*e;
  p0=sqrt(energy0*energy0/c/c+2.0*energy0*m);

  out=fopen("Ex","w");
  for(x=0; x<=100*50e-9; x+=10e-9)
  {
    field=Efield(x,density);
    fprintf(out,"%g %g\n",x,field);
  }
  fclose(out);


  x=x0;
  p=p0;
  for(i=0; i<=final; i++)
  {
    t=dt*i;
    field=e*Efield(x,density);
    p+=field*dt;
    gamma=sqrt(1.0+p*p/m/m/c/c);
    x+=p/gamma/m*dt;
    printf("%g %g %g\n",x,p/m/c,gamma);
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
  float e,eps0,A,result,incline;

  e=1.601e-19;
  eps0=8.85e-12;
  A=50e-9*50e-9*3.14;
  incline=-0.5/3.14/eps0*e*n*A/50e-9;
  if(x>=50e-9)
    result=-0.5/3.14/eps0*e*n*A/x;
  else if(x>=0.0 && x<50e-9)
    result=incline*x;

  return result;
}  
