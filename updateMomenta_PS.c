#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include <math.h>
//#include "mpi.h"

void updateMomenta(Parameter *D,PonderScat *PS,Laser *L,float t)
{
  float a0,sigmaX,sigmaY,x,y,dt,tau,px,py,oldPx,oldPy,gamma,a;
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
      x=p->oldX;
      y=p->oldY;
      oldPx=p->Px;
      oldPy=p->Py;

      //calculating Px
      px=oldPx;
      py=oldPy;
      tau=t;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx1=1.0/gamma*(x-t)/sigmaX/sigmaX*a*a;

      px=oldPx+0.5*dt*kx1;
      py=oldPy;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx2=1.0/gamma*(x-t)/sigmaX/sigmaX*a*a;

      px=oldPx+0.5*dt*kx2;
      py=oldPy;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx3=1.0/gamma*(x-t)/sigmaX/sigmaX*a*a;

      px=oldPx+dt*kx3;
      py=oldPy;
      tau=t+dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      kx4=1.0/gamma*(x-t)/sigmaX/sigmaX*a*a;

      //calculating Py
      px=oldPx;
      py=oldPy;
      tau=t;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky1=1.0/gamma*y/sigmaY/sigmaY*a*a;

      px=oldPx;
      py=oldPy+0.5*dt*ky1;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky2=1.0/gamma*y/sigmaY/sigmaY*a*a;

      px=oldPx;
      py=oldPy+0.5*dt*ky2;
      tau=t+0.5*dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky3=1.0/gamma*y/sigmaY/sigmaY*a*a;

      px=oldPx;
      py=oldPy+dt*ky3;
      tau=t+dt;
      a=laser2D(tau,x,y,a0,sigmaX,sigmaY);
      gamma=sqrt(1.0+px*px+py*py+0.5*a*a);	//linear
      ky4=1.0/gamma*y/sigmaY/sigmaY*a*a;

      //update momentum
      p->Px=oldPx+dt/6.0*(kx1+kx2+kx3+kx4);
      p->oldPx=0.5*(p->Px+oldPx);
      p->Py=oldPy+dt/6.0*(ky1+ky2+ky3+ky4);
      p->oldPy=0.5*(p->Py+oldPy);

      p=p->next;
    }
    break;
  }

}

