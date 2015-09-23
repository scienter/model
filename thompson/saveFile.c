#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include <math.h>
//#include "mpi.h"

void saveField(Parameter *D,int iteration)
{
  float x,y,z,dx,dy,Epot,minX,minY;
  int i,j,k;
  char name[100];
  FILE *out;
//  int myrank, nprocs;    
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  
  dx=D->dx;
  dy=D->dy;
  minX=D->minX;
  minY=D->minY;

  switch (D->dimension)
  {
    case 2:
    k=0;
    sprintf(name,"Efield%d",iteration);
    out = fopen(name,"w");  
    for(i=0; i<D->nx; i++)
    {
      x=i*dx+minX;
      for(j=0; j<D->ny; j++)
      {
        y=j*dy+minY;
        Epot=D->V[i][j][k];
        fprintf(out,"%g %g %g\n",x,y,Epot);
      }               
      fprintf(out,"\n");
    }	
    fclose(out);
    break;
  }
}
/*
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
*/
