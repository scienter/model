#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include <math.h>
//#include "mpi.h"

void saveParticle(Parameter *D,int iteration)
{
  float x,y,z,px,py,pz,gamma;
  int index;
  char name[100];
  ptclList *p;
  FILE *out;
//  int myrank, nprocs;    
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  switch (D->dimension)
  {
    case 2:
    sprintf(name,"particle%d",iteration);
    out = fopen(name,"w");    
    p=D->head;
    while(p)
    {
      x=p->x/D->kp; 
      y=p->y/D->kp; 
      px=p->Px;
      py=p->Py;
      gamma=sqrt(1.0+px*px+py*py);
      index=p->index;
      fprintf(out,"%g %g %g %g %g %d\n",x,y,px,py,gamma,index);               
      p=p->next;
    }	//End of while(p)
    fclose(out);
    break;
  }
}

void saveLaser(Parameter *D,PonderScat *PS,Laser *L,int iteration,float t)
{
  float x,y,z,field,x0,x1,y0,y1,dx,dy;
  int index;
  char name[100];
  ptclList *p;
  FILE *out;
//  int myrank, nprocs;    
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  switch (D->dimension)
  {
    case 2:
    sprintf(name,"laser%d",iteration);
    out = fopen(name,"w");    

    x0=L->minX;
    x1=L->maxX;
    y0=L->minY;
    y1=L->maxY;
    dx=PS->lambda/PS->divisionLambda*D->kp;
    dy=dx*PS->dyOverDx;

    for(x=x0; x<=x1; x+=dx)
    {
      for(y=y0; y<=y1; y+=dy)
      {
        field=laser2D(t,x,y,L->a0,L->sigmaX,L->sigmaY);
        fprintf(out,"%g %g %g\n",x/D->kp,y/D->kp,field);
      }               
      fprintf(out,"\n");
    }

    fclose(out);
    break;
  }
}

