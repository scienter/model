#include "stdio.h"
#include "stdlib.h"
#include "math.h"
main(int argc, char *argv[])
{
   int i,numX,start,end,saveStep,step;
   float minX,maxX,x,px,py,pz,gamma,dx,beta;
   float *v,*fn;
   char name[100];
   FILE *in,*out;

   if(argc<6)
   {
     printf("saveDensity [start] [end] [step] [minX] [maxX] [numX]\n");
     exit(0);
   }
   start=atoi(argv[1]);
   end=atoi(argv[2]);
   saveStep=atoi(argv[3]);
   minX= atof(argv[4]);
   maxX= atof(argv[5]);
   numX= atoi(argv[6]);
   dx=(maxX-minX)/((float) numX);

   v=(float *)malloc(numX*sizeof(float ));
   fn=(float *)malloc(numX*sizeof(float ));

   for(step=start; step<=end; step+=saveStep)
   {
     for(i=0; i<numX; i++)
     {
       v[i]=minX+i*dx;
       fn[i]=0.0;
     }

     sprintf(name,"particle%d",step);
     in = fopen(name,"r");
//      fgets(str,100,inCen);       
     while(fscanf(in,"%g %g %g %g %g",&x,&px,&py,&pz,&gamma)!=EOF) 
     {
       i=(int)((x-minX)/dx);
       if(i>=0 && i<numX)
         fn[i]+=1.0;
     }
     fclose(in);

     sprintf(name,"density%d",step);
     out = fopen(name,"w");
     for(i=0; i<numX; i++)
       fprintf(out,"%g %g\n",v[i],fn[i]);
     fclose(out);
     printf("density%d is saved\n",step);
   }

   free(v);
   free(fn);
}
