#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <time.h>
#include "parameter.h"

int main(int argc, char *argv[])
{
   int iteration=0;
   float t;
   char name[100];
   FILE *out;
//   int myrank, nTasks;
//   MPI_Status status; 

//   MPI_Init(&argc,&argv);
//   MPI_Comm_size(MPI_COMM_WORLD, &nTasks);
//   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   Parameter D;
   PonderScat PS;
   Laser L;

   //parameter setting
   parameterSetting(&D,&PS,&L,argv[1]);
   
   switch (D.mode)  {
     case PonderoScat :
     boundary_PS(&D,&PS);
     
     while(iteration<=D.finalStep)
     {
       t=iteration*PS.dt;
       
       if(iteration%D.saveStep==0)
       {
         saveParticle(&D,iteration);
//         saveLaser(&D,&PS,&L,iteration,t);
         printf("At iteration=%d, files are saved.\n",iteration);
       }

       updateMomenta(&D,&PS,&L,t);       
       updatePosition(&D,&PS,&L,t);       

       if(iteration%10==0)
         printf("iteration=%d\n",iteration);
       iteration++;
     }
      
     break;

   }
 
//   MPI_Finalize();

   return 0;
}
