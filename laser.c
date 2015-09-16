#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include <math.h>
//#include "mpi.h"

float laser2D(float t,float x,float y,float a0,float sigmaX,float sigmaY)
{
  float result,sigmaX2,sigmaY2;
  
  sigmaX2=sigmaX*sigmaX;
  sigmaY2=sigmaY*sigmaY;
  result=a0*exp(-(x-t)*(x-t)/sigmaX2)*exp(-y*y/sigmaY2);

  return result; 
}

