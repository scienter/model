#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "constants.h"
#include <math.h>
//#include "mpi.h"

void updatePx_X(Parameter *D)
{
  float x,dt,density,field,gamma,oldPx,tmp;
  int cnt;
  ptclList *p;
  
  dt=D->dt;
  density=D->density;

  switch (D->dimension)  {
    case 2  :
    p=D->head;
    while(p)
    {
      x=p->x;
      field=eCharge*Efield(x,density);
      p->px-=field*dt;
      gamma=sqrt(1.0+p->px*p->px/eMass/eMass/velocityC/velocityC);
      p->x+=p->px/gamma/eMass*dt;

      p=p->next;
    }
    break;
  }

}

