#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parameter.h"
#include "constants.h"

//#include "mpi.h"

float Efield(float x,float n)
{
  float A,result,incline,r0;

  r0=50e-9;
  A=50e-9*r0*3.14;
  incline=0.5/3.14/eps0*eCharge*n*A/(r0*r0);
  if(x>r0)
    result=0.5/3.14/eps0*eCharge*n*A/x;
  else if(x>=-r0 && x<=r0)
    result=incline*x;
  else if(x<-r0)
    result=0.5/3.14/eps0*eCharge*n*A/x;

  return result;
}  
