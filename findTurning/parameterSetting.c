#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameter.h"
#include "constants.h"
#include <math.h>
//#include <mpi.h>
#include <time.h>


void parameterSetting(Parameter *D,char *input)
{
  int fail=0;
  float backDensity;
  char str[100];
  int whatCalType();
//   int myrank, nTasks;
//   MPI_Status status;

//   MPI_Comm_size(MPI_COMM_WORLD, &nTasks);     
//   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);     

   FILE *out;


   //initially
   if(FindParameters("Parameter",1,"dimension",input,str)) D->dimension=atoi(str);
   else  {
     printf("in [Parameter], dimension=?  (1:1D, 2:2D, 3:3D)\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"final_step",input,str))
     D->finalStep=atoi(str);
   else  {
     printf("in [Parameter], final_step=?\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"save_step",input,str))
     D->saveStep=atoi(str);
   else  {
     printf("in [Parameter], save_step=?\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"x0",input,str))
     D->x0=atof(str);
   else  {
     printf("in [Parameter], x0=?\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"rangeX",input,str))
     D->rangeX=atof(str);
   else  {
     printf("in [Parameter], rangeX=?\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"dt",input,str))
     D->dt=atof(str);
   else  {
     printf("in [Parameter], dt=?  [ex)3.33e-17]\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"density",input,str))
     D->density=atof(str);
   else  {
     printf("in [Parameter], density=?  [SI]\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"totalCnt",input,str))
     D->totalCnt=atoi(str);
   else  {
     printf("in [Parameter], totalCnt=?  [ea]\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"temperature",input,str))
     D->temperature=atof(str);
   else  {
     printf("in [Parameter], temperature=?  [eV]\n");
      fail=1;
   }
   if(fail==1)
     exit(0);
}
