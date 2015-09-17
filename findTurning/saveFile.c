#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "constants.h"
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
      x=p->x; 
//      y=p->y/D->kp; 
      px=p->px/eMass/velocityC;
      py=p->py/eMass/velocityC;
      pz=p->pz/eMass/velocityC;
      gamma=sqrt(1.0+px*px+py*py+pz*pz);
      index=p->index;
      fprintf(out,"%g %g %g %g %g\n",x,px,py,pz,gamma);               
      p=p->next;
    }	//End of while(p)
    fclose(out);
    printf("particle%d is made\n",iteration);
    break;
  }
}
