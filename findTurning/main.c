#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parameter.h"
#include "constants.h"

//#include "mpi.h"

int main(int argc, char *argv[])
{
  int i,final;
  float x,dt,t,field;
  FILE *out;
  char name[100];
  void particleDistribution();
  Parameter D;
  
  
//  energy0=energy0*e;
//  p0=sqrt(energy0*energy0/c/c+2.0*energy0*m);
  parameterSetting(&D,argv[1]);

  out=fopen("Ex","w");
  for(x=-100*50e-9; x<=100*50e-9; x+=10e-9)
  {
    field=Efield(x,D.density);
    fprintf(out,"%g %g\n",x,field);
  }
  fclose(out);
  printf("Ex file is made\n");

  particleDistribution(&D);
//  saveParticle(&D,0);

  final=D.finalStep;
  dt=D.dt;
  for(i=0; i<=final; i++)
  {
    t=dt*i;
    updatePx_X(&D);

    if(i%D.saveStep==0)
      saveParticle(&D,i);
  }
  
  cleanMemory(&D);
  return 0;
}

void particleDistribution(Parameter *D)
{
  int totalCnt,cnt;
  float startX,rangeX,m;
  ptclList *New;
  float randomV();
  float maxwellianVelocity(float temperature);

  D->head=NULL;
  totalCnt=D->totalCnt;
  startX=D->x0;
  rangeX=D->rangeX;
//here

  cnt=0;
  while(cnt<totalCnt)
  {
    New=(ptclList *)malloc(sizeof(ptclList));
    New->next=D->head;
    D->head=New;
    New->x=startX+randomV()*rangeX;
    New->px=maxwellianVelocity(D->temperature)*eMass;
    New->py=maxwellianVelocity(D->temperature)*eMass;
    New->pz=maxwellianVelocity(D->temperature)*eMass;
   
    cnt++;
  }

}

float maxwellianVelocity(float temperature)
{
   float vth,r,prob,v,random;
   int intRand,randRange=1e5;

   vth=sqrt(2.0*eCharge*temperature/eMass);

   r=1.0;
   prob=0.0;
   while (r>prob)  {
      intRand = rand() % randRange;
      r = ((float)intRand)/randRange;
      intRand = rand() % randRange;
      random = ((float)intRand)/randRange;
      v = 6.0*(random-0.5);
      prob=exp(-v*v);
   }
   return vth*v;
}



float randomV()
{
   float r;
   int intRand, randRange=1000, rangeDev;

   intRand = rand() % randRange;
   r = ((float)intRand)/randRange;

   return r;
}

