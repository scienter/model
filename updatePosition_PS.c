#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include <math.h>
//#include "mpi.h"

void updatePosition(Parameter *D,PonderScat *PS,Laser *L,float t)
{
  float a0,sigmaX,sigmaY,x,y,dt,tau,px,py,oldX,oldY,gamma,a;
  float kx1,kx2,kx3,kx4,ky1,ky2,ky3,ky4;
  ptclList *p;

  a0=L->a0;
  sigmaX=L->sigmaX;
  sigmaY=L->sigmaY;
  dt=PS->dt;

  switch (D->dimension)  {
    case 2  :
    p=D->head;
    while(p)
    {
      px=p->oldPx;
      py=p->oldPy;
      oldX=p->x;
      oldY=p->y;

      //calculating x
      x=oldX;
      y=oldY;
      tau=t;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx1=px/gamma;

      x=oldX+0.5*dt*kx1;
      y=oldY;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx2=px/gamma;

      x=oldX+0.5*dt*kx2;
      y=oldY;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx3=px/gamma;

      x=oldX+dt*kx3;
      y=oldY;
      tau=t+dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx4=px/gamma;

      //calculating Py
      x=oldX;
      y=oldY;
      tau=t;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky1=py/gamma;

      x=oldX;
      y=oldY+0.5*dt*ky1;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky2=py/gamma;

      x=oldX;
      y=oldY+0.5*dt*ky2;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky3=py/gamma;

      x=oldX;
      y=oldY+dt*ky3;
      tau=t+dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky4=py/gamma;

      //update momentum
      p->x=oldX+dt/6.0*(kx1+kx2+kx3+kx4);
      p->oldX=0.5*(p->x+oldX);
      p->y=oldY+dt/6.0*(ky1+ky2+ky3+ky4);
      p->oldY=0.5*(p->y+oldY);

      p=p->next;
    }
    break;
  }

}

