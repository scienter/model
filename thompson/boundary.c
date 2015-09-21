#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
//#include <mpi.h>

void boundary(Parameter *D)
{
  int nx,ny,nz,i,j,k;
  ptclList *New;
  FILE *out;
  float randomV();

  nx=D->nx;
  ny=D->ny;
  nz=1;
//  MPI_Status status;
//  MPI_Comm_size(MPI_COMM_WORLD, &nTasks);     
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);     

  D->Ex=(float ***)malloc(nx*sizeof(float **));
  D->Ey=(float ***)malloc(nx*sizeof(float **));
  for(i=0; i<nx; i++)
  {
    D->Ex[i]=(float **)malloc(ny*sizeof(float *));
    D->Ey[i]=(float **)malloc(ny*sizeof(float *));
    for(j=0; j<ny; j++)
    {
      D->Ex[i][j]=(float *)malloc(nz*sizeof(float ));
      D->Ey[i][j]=(float *)malloc(nz*sizeof(float ));
    }
  }

  k=0;
  for(i=0; i<nx; i++)
    for(j=0; j<ny; j++)
    {
      D->Ex[i][j][k]=0.0;
      D->Ey[i][j][k]=0.0;
    }

   

/*
    D->head=NULL;
    rangeX=PS->maxX-PS->minX;
    rangeY=PS->maxY-PS->minY;
    startX=PS->minX;
    startY=PS->minY;
    totalCnt=(int)((rangeX/D->kp*rangeY/D->kp)/dx/dy*PS->numberInCell);
    
    cnt=0;
    while(cnt<totalCnt)
    {
      New=(ptclList *)malloc(sizeof(ptclList));
      New->next=D->head;
      D->head=New;
      New->oldX=startX+randomV()*rangeX;
      New->oldY=startY+randomV()*rangeY;
      New->x=New->oldX;
      New->y=New->oldY;
      New->oldPx=PS->Px0;
      New->oldPy=PS->Py0;
      New->Px=New->oldPx;
      New->Py=New->oldPy;
      New->index=cnt;
      cnt++;
    }
*/
}

float randomV()
{
   float r;
   int intRand, randRange=1000, rangeDev;

   intRand = rand() % randRange;
   r = ((float)intRand)/randRange;

   return r;
}

