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
  int fail=0,i,j,k;
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
   if(FindParameters("Parameter",1,"minX",input,str)) D->minX=atof(str);
   else  {
     printf("in [Parameter], minX=?  [SI]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"maxX",input,str)) D->maxX=atof(str);
   else  {
     printf("in [Parameter], maxX=?  [SI]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"minY",input,str)) D->minY=atof(str);
   else  {
     printf("in [Parameter], minY=?  [SI]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"maxY",input,str)) D->maxY=atof(str);
   else  {
     printf("in [Parameter], maxY=?  [SI]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"nx",input,str)) D->nx=atoi(str);
   else  {
     printf("in [Parameter], nx=?  \n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"ny",input,str)) D->ny=atoi(str);
   else  {
     printf("in [Parameter], ny=?  \n");
     fail=1;
   }
   D->dx=(D->maxX-D->minX)/((float)D->nx);
   D->dy=(D->maxY-D->minY)/((float)D->ny);

   //Electrode
   if(FindParameters("Parameter",1,"Epotential",input,str)) D->Epot=atof(str);
   else  {
     printf("in [Electrode], Epotential=?  [eV]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"Enodes",input,str)) D->Enodes=atoi(str);
   else  {
     printf("in [Electrode], Enodes=?  \n");
     fail=1;
   }
   if(D->Enodes>0)
   {
     D->elec=(float **)malloc(D->Enodes*sizeof(float *));
     for(i=0; i<D->Enodes; i++)
       D->elec[i]=(float *)malloc(3*sizeof(float ));

     for(i=0; i<D->Enodes-1; i++)
     {
       sprintf(str,"x%d",i);
       if(FindParameters("Parameter",1,str,input,str))
         D->elec[i][0]=atof(str);
       else  {
         printf("in [Electrode], x%d=?  \n",i);
         fail=1;
       }
       sprintf(str,"y%d",i);
       if(FindParameters("Parameter",1,str,input,str))
         D->elec[i][1]=atof(str);
       else  {
         printf("in [Electrode], y%d=?  \n",i);
         fail=1;
       }
     }

   }
      
   //Magnet
   if(FindParameters("Parameter",1,"Mpotential",input,str)) D->Mpot=atof(str);
   else  {
     printf("in [Magnet], Mpotential=?  [eV]\n");
     fail=1;
   }
   if(FindParameters("Parameter",1,"Mnodes",input,str)) D->Mnodes=atoi(str);
   else  {
     printf("in [Magnet], Mnodes=?  \n");
     fail=1;
   }
   if(D->Mnodes>0)
   {
     D->magnet=(float **)malloc(D->Mnodes*sizeof(float *));
     for(i=0; i<D->Mnodes; i++)
       D->magnet[i]=(float *)malloc(3*sizeof(float ));

     for(i=0; i<D->Mnodes-1; i++)
     {
       sprintf(str,"x%d",i);
       if(FindParameters("Parameter",1,str,input,str))
         D->magnet[i][0]=atof(str);
       else  {
         printf("in [Magnet], x%d=?  \n",i);
         fail=1;
       }
       sprintf(str,"y%d",i);
       if(FindParameters("Parameter",1,str,input,str))
         D->magnet[i][1]=atof(str);
       else  {
         printf("in [Magnet], y%d=?  \n",i);
         fail=1;
       }
     }

   }




   if(fail==1)
     exit(0);


}

