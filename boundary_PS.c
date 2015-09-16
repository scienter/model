#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
//#include <mpi.h>

void boundary_PS(Parameter *D,PonderScat *PS)
{
  int cnt,totalCnt;
  float rangeX,rangeY,rangeZ,startX,startY,dx,dy,dz;
  ptclList *New;
  FILE *out;
  float randomV();

//  MPI_Status status;
//  MPI_Comm_size(MPI_COMM_WORLD, &nTasks);     
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);     
  PS->dt=PS->lambda/PS->divisionLambda*D->kp;
  dx=PS->lambda/PS->divisionLambda;
  dy=dx*PS->dyOverDx;
  dz=dx*PS->dzOverDx;

  // Particle setting
  switch (D->dimension)  {
    case 2  :
    


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

    break;

  }
}

float randomV()
{
   float r;
   int intRand, randRange=1000, rangeDev;

   intRand = rand() % randRange;
   r = ((float)intRand)/randRange;

   return r;
}

