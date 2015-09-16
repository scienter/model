#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameter.h"
#include "constants.h"
#include <math.h>
//#include <mpi.h>
#include <time.h>


void parameterSetting(Parameter *D,PonderScat *PS,Laser *L,char *input)
{
  int fail=0;
  float backDensity;
  char str[100];
  int whatCalType();
  void find_PonderoScat_Parameter();
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
   if(FindParameters("Parameter",1,"calculation_mode",input,str))
     D->mode=whatCalType(str);
   else  {
     printf("in [Parameter], calculation_mode=?\n");
     printf("ponderomotive_scattering\n");
      fail=1;
   }
   if(FindParameters("Parameter",1,"max_step",input,str)) D->finalStep=atof(str);
   else  {
     printf("in [Parameter], max_step=?  \n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"save_step",input,str)) D->saveStep=atof(str);
   else  {
     printf("in [Parameter], save_step=?  \n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"save_start",input,str)) D->saveStart=atof(str);
   else  {
     printf("in [Parameter], save_start=?  \n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"background_density",input,str)) backDensity=atof(str);
   else  {
     printf("in [Parameter], background_density=?  [SI]\n");
     fail=1;
   }
   D->wp=sqrt(eCharge*eCharge*backDensity/eps0/eMass);
   D->kp=D->wp/velocityC;

   //laser
   if(FindParameters("Laser",1,"a0",input,str)) L->a0=atof(str);
   else  {
     printf("in [Laser], a0=?  \n");
     fail=1;
   }
   if(FindParameters("Laser",1,"sigmaX",input,str)) L->sigmaX=atof(str)*D->kp;
   else  {
     printf("in [Laser], sigmaX=?  [m]\n");
     fail=1;
   }
   if(FindParameters("Laser",1,"minX",input,str)) L->minX=atof(str)*D->kp;
   else  {
     printf("in [Laser], minX=?  [m]\n");
     fail=1;
   }
   if(FindParameters("Laser",1,"maxX",input,str)) L->maxX=atof(str)*D->kp;
   else  {
     printf("in [Laser], maxX=?  [m]\n");
     fail=1;
   }
   if(D->dimension>1)
   {
     if(FindParameters("Laser",1,"sigmaY",input,str)) L->sigmaY=atof(str)*D->kp;
     else  {
       printf("in [Laser], sigmaY=?  [m]\n");
       fail=1;
     }
     if(FindParameters("Laser",1,"minY",input,str)) L->minY=atof(str)*D->kp;
     else  {
       printf("in [Laser], minY=?  [m]\n");
       fail=1;
     }
     if(FindParameters("Laser",1,"maxY",input,str)) L->maxY=atof(str)*D->kp;
     else  {
       printf("in [Laser], maxY=?  [m]\n");
       fail=1;
     }
   }
   if(D->dimension>2)
   {
     if(FindParameters("Laser",1,"sigmaZ",input,str)) L->sigmaZ=atof(str)*D->kp;
     else  {
       printf("in [Laser], sigmaZ=?  [m]\n");
       fail=1;
     }
     if(FindParameters("Laser",1,"minZ",input,str)) L->minZ=atof(str)*D->kp;
     else  {
       printf("in [Laser], minZ=?  [m]\n");
       fail=1;
     }
     if(FindParameters("Laser",1,"maxZ",input,str)) L->maxZ=atof(str)*D->kp;
     else  {
       printf("in [Laser], maxZ=?  [m]\n");
       fail=1;
     }
   }

   if(fail==1)
     exit(0);

   if(D->mode==PonderoScat)
     find_PonderoScat_Parameter(D,PS,input);

}

void find_PonderoScat_Parameter(Parameter *D,PonderScat *PS,char *input)
{
   int fail=0;
   char str[100];
   if(FindParameters("Ponderomotive_Scattering",1,"density",input,str))
     PS->density=atof(str);
   else  {
      printf("in [Ponderomotive_Scattering], density=?\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"minX",input,str))
     PS->minX=atof(str)*D->kp;
   else  {
      printf("in [Ponderomotive_Scattering], minX=? [m]\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"maxX",input,str))
     PS->maxX=atof(str)*D->kp;
   else  {
      printf("in [Ponderomotive_Scattering], maxX=? [m]\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"lambda",input,str))
     PS->lambda=atof(str);
   else  {
      printf("in [Ponderomotive_Scattering], lambda=? [m]\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"division_lambda",input,str))
     PS->divisionLambda=atof(str);
   else  {
      printf("in [Ponderomotive_Scattering], division_lambda=? [m]\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"number_in_cell",input,str))
     PS->numberInCell=atof(str);
   else  {
      printf("in [Ponderomotive_Scattering], number_in_cell=? [m]\n");
      fail=1;
   }
   if(FindParameters("Ponderomotive_Scattering",1,"Px0",input,str))
     PS->Px0=atof(str);
   else { 
      printf("in [Ponderomotive_Scattering], Px0=? [m]\n");
      fail=1;
   }
   
   if(D->dimension>1)
   {
     if(FindParameters("Ponderomotive_Scattering",1,"dy_over_dx",input,str))
       PS->dyOverDx=atof(str);
     else  {
        printf("in [Ponderomotive_Scattering], dy_over_dx=? [m]\n");
        fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"minY",input,str))
       PS->minY=atof(str)*D->kp;
     else  {
        printf("in [Ponderomotive_Scattering], minY=? [m]\n");
        fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"maxY",input,str))
       PS->maxY=atof(str)*D->kp;
     else  {
       printf("in [Ponderomotive_Scattering], maxY=? [m]\n");
       fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"Py0",input,str))
       PS->Py0=atof(str);
     else  {
       printf("in [Ponderomotive_Scattering], Py0=? [m]\n");
       fail=1;
     }
   }
   if(D->dimension>2)
   {
     if(FindParameters("Ponderomotive_Scattering",1,"dz_over_dx",input,str))
       PS->dyOverDx=atof(str);
     else  {
        printf("in [Ponderomotive_Scattering], dz_over_dx=? [m]\n");
        fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"minZ",input,str))
       PS->minZ=atof(str)*D->kp;
     else  {
       printf("in [Ponderomotive_Scattering], minZ=? [m]\n");
       fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"maxZ",input,str))
       PS->maxZ=atof(str)*D->kp;
     else  {
       printf("in [Ponderomotive_Scattering], maxZ=? [m]\n");
       fail=1;
     }
     if(FindParameters("Ponderomotive_Scattering",1,"Pz0",input,str))
       PS->Pz0=atof(str);
     else  {
       printf("in [Ponderomotive_Scattering], Pz0=? [m]\n");
       fail=1;
     }
   }

   if(fail==1)
     exit(0);


}


int whatCalType(char *str)
{
   if(strstr(str,"ponderomotive_scattering"))           return PonderoScat;
   else return 0;
}

