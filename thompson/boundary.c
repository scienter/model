#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
//#include <mpi.h>

void boundary(Parameter *D)
{
  int n,nx,ny,nz,i,j,k,iStart,iEnd,jStart,jEnd,cnt,indexY[2];
  float dx,dy,minX,minY,x1,y1,x2,y2,x,y,upX,btX,upY,btY;
  ptclList *New;
  LoadList *LL;
  FILE *out;
  float randomV();
  float func(float x,float x1,float y1,float x2,float y2);

  indexY[0]=0;
  indexY[1]=0;
  nx=D->nx;
  ny=D->ny;
  nz=1;
  dx=D->dx;
  dy=D->dy;
  minX=D->minX;
  minY=D->minY;

//  MPI_Status status;
//  MPI_Comm_size(MPI_COMM_WORLD, &nTasks);     
//  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);     

  D->V=(float ***)malloc(nx*sizeof(float **));
  D->M=(float ***)malloc(nx*sizeof(float **));
  for(i=0; i<nx; i++)
  {
    D->V[i]=(float **)malloc(ny*sizeof(float *));
    D->M[i]=(float **)malloc(ny*sizeof(float *));
    for(j=0; j<ny; j++)
    {
      D->V[i][j]=(float *)malloc(nz*sizeof(float ));
      D->M[i][j]=(float *)malloc(nz*sizeof(float ));
    }
  }

  k=0;
  for(i=0; i<nx; i++)
    for(j=0; j<ny; j++)
    {
      D->V[i][j][k]=0.0;
      D->M[i][j][k]=0.0;
    }

  //making Electrode boundary
  LL=D->EloadList;
  while(LL->next)
  {
    for(n=0; n<LL->nodes-1; n++)
    {
      x1=LL->points[n][0];
      y1=LL->points[n][1];
      x2=LL->points[n+1][0];
      y2=LL->points[n+1][1];
    
      if(x1==x2)
      {
        if(y1>=y2) {
          jEnd=(int)((y1-minY)/dy);
          jStart=(int)((y2-minY)/dy);
        }
        else  {
          jEnd=(int)((y2-minY)/dy);
          jStart=(int)((y1-minY)/dy);
        }
        i=(int)((x1-minX)/dx);
        for(j=jStart; j<=jEnd; j++)
        {
          D->V[i][j][k]=LL->pot;
        }
      }

      else
      {
        if(x1>x2) {
          iStart=(int)((x2-minX)/dx);
          iEnd=(int)((x1-minX)/dx);
        }
        else  {
          iStart=(int)((x1-minX)/dx);
          iEnd=(int)((x2-minX)/dx);
        }
        for(i=iStart; i<=iEnd; i++)
        {
          x=i*dx+minX;
          y=func(x,x1,y1,x2,y2);
          j=(int)((y-minY)/dy);
          D->V[i][j][k]=LL->pot;
        }
      }
    }	//End of electrode boundary


    //filling area of electrode.
    btX=1e5;
    btY=1e5;
    upX=-1e5;
    upY=-1e5;
    for(n=0; n<LL->nodes-1; n++)
    {
      x1=LL->points[n][0];
      if(x1<btX) btX=x1;
      else if(x1>upX) upX=x1;
      else	;
      y1=LL->points[n][1];
      if(y1<btY) btY=y1;
      else if(y1>upY) upY=y1;
      else	;
    }
    iStart=(int)((btX-minX)/dx);
    iEnd=(int)((upX-minX)/dx);
    jStart=(int)((btY-minY)/dy);
    jEnd=(int)((upY-minY)/dy);
 
    for(i=iStart; i<=iEnd; i++)
    {
      cnt=0;
      for(j=jStart; j<=jEnd; j++)
      {
        if(D->V[i][j][k]!=0 && cnt<2)
        {
          indexY[cnt]=j;
          cnt++;
        }
      }      
    
      if(cnt==2)
        for(j=indexY[0]; j<=indexY[1]; j++)
          D->V[i][j][k]=LL->pot;
    }	//End of filling electrode    


    LL=LL->next;
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

float func(float x,float x1,float y1,float x2,float y2)
{
  float incline, result;

  incline=(y2-y1)/(x2-x1);
  result=incline*(x-x1)+y1;

  return result;
}

float randomV()
{
   float r;
   int intRand, randRange=1000, rangeDev;

   intRand = rand() % randRange;
   r = ((float)intRand)/randRange;

   return r;
}

