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
  int fail=0,i,j,k,rank;
  char str[100];
  int whatCalType();
  int findElectrodeParameters();
//   int myrank, nTasks;
//   MPI_Status status;

//   MPI_Comm_size(MPI_COMM_WORLD, &nTasks);     
//   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);     
  LoadList *LL,*New;
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
   D->EloadList=(LoadList *)malloc(sizeof(LoadList));
   D->EloadList->next=NULL;
   LL=D->EloadList;
   rank=1;   
   sprintf(str,"Electrode");
   while(findElectrodeParameters(rank,D,LL,input,str))
   {
     printf("rank=%d, potential=%g\n",rank,LL->pot);
     New=(LoadList *)malloc(sizeof(LoadList));
     New->next=NULL;
     LL->next=New;
     LL=LL->next;
     rank++;
   }
/*
   D->Enodes=0;
   if(FindParameters("Electrode",1,"Enodes",input,str)) D->Enodes=atoi(str);
   else  {
     printf("in [Electrode], Enodes=?  \n");
     fail=1;
   }
   if(D->Enodes>0)
   {
     D->Enodes+=1;
     D->elec=(float **)malloc(D->Enodes*sizeof(float *));
     for(i=0; i<D->Enodes; i++)
       D->elec[i]=(float *)malloc(3*sizeof(float ));

     for(i=0; i<D->Enodes-1; i++)
     {
       sprintf(str,"x%d",i);
       if(FindParameters("Electrode",1,str,input,str))
         D->elec[i][0]=atof(str);
       else  {
         printf("in [Electrode], x%d=?  \n",i);
         fail=1;
       }
       sprintf(str,"y%d",i);
       if(FindParameters("Electrode",1,str,input,str))
         D->elec[i][1]=atof(str);
       else  {
         printf("in [Electrode], y%d=?  \n",i);
         fail=1;
       }
     }
     D->elec[D->Enodes-1][0]=D->elec[0][0];
     D->elec[D->Enodes-1][1]=D->elec[0][1];

   }
      
   //Magnet
   if(FindParameters("Magnet",1,"Mpotential",input,str)) D->Mpot=atof(str);
   else  {
     printf("in [Magnet], Mpotential=?  [eV]\n");
     fail=1;
   }
   D->Mnodes=0;
   if(FindParameters("Magnet",1,"Mnodes",input,str)) D->Mnodes=atoi(str);
   else  {
     printf("in [Magnet], Mnodes=?  \n");
     fail=1;
   }
   if(D->Mnodes>0)
   {
     D->Mnodes+=1;
     D->magnet=(float **)malloc(D->Mnodes*sizeof(float *));
     for(i=0; i<D->Mnodes; i++)
       D->magnet[i]=(float *)malloc(3*sizeof(float ));

     for(i=0; i<D->Mnodes-1; i++)
     {
       sprintf(str,"x%d",i);
       if(FindParameters("Magnet",1,str,input,str))
         D->magnet[i][0]=atof(str);
       else  {
         printf("in [Magnet], x%d=?  \n",i);
         fail=1;
       }
       sprintf(str,"y%d",i);
       if(FindParameters("Magnet",1,str,input,str))
         D->magnet[i][1]=atof(str);
       else  {
         printf("in [Magnet], y%d=?  \n",i);
         fail=1;
       }
     }
     D->magnet[D->Mnodes-1][0]=D->magnet[0][0];
     D->magnet[D->Mnodes-1][1]=D->magnet[0][1];

   }
*/



   if(fail==1)
     exit(0);


}

int findElectrodeParameters(int rank,Parameter *D,LoadList *LL,char *input,char *block)
{
  int nodes,i,fail=0;
  char str[100],name[100];
  int FindParameters();

  if(FindParameters(block,rank,"nodes",input,str)) LL->nodes=atoi(str);
  else  LL->nodes=0;
  if(LL->nodes)
  {
    if(FindParameters(block,rank,"potential",input,str)) LL->pot=atof(str);
    else  {
      printf("in [%s], potential=?  [electric:eV, magnetic:flux]\n",block);
      fail=1;
    }
    LL->nodes+=1;
    LL->points=(float **)malloc(LL->nodes*sizeof(float *));
    for(i=0; i<LL->nodes; i++)
      LL->points[i]=(float *)malloc(3*sizeof(float ));

    for(i=0; i<LL->nodes-1; i++)
    {
      sprintf(name,"x%d",i);
      if(FindParameters(block,rank,name,input,str))
        LL->points[i][0]=atof(str);
      else  {
        printf("in [%s], x%d=?  \n",block,i);
        fail=1;
      }
      sprintf(name,"y%d",i);
      if(FindParameters(block,rank,name,input,str))
        LL->points[i][1]=atof(str);
      else  {
        printf("in [%s], y%d=?  \n",block,i);
        fail=1;
      }
    }
    LL->points[LL->nodes-1][0]=LL->points[0][0];
    LL->points[LL->nodes-1][1]=LL->points[0][1];
  }

  if(fail==1)
    exit(0);
 
  return LL->nodes;
}
