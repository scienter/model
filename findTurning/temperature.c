#include "stdio.h"
#include "stdlib.h"
#include "math.h"
main(int argc, char *argv[])
{
   int i;
   float numV,minV,maxV,x,px,py,pz,gamma,dV,beta;
   float *v,*fn;
   FILE *in;

   numV= atof(argv[2]);
   if(argc<2)
   {
     printf("temperature [file] [numV]\n");
     exit(0);
   }

   minV=100;
   maxV=-100;
   in = fopen(argv[1],"r");
//      fgets(str,100,inCen);       
   while(fscanf(in,"%g %g %g %g %g",&x,&px,&py,&pz,&gamma)!=EOF) 
   {
     if(px/gamma<=minV)  minV=px/gamma;
     else if(px/gamma>maxV)  maxV=px/gamma;
     else	;
   }
   fclose(in);

   minV=minV*2;
   maxV=maxV*2;
   dV=(maxV-minV)/numV;
   v=(float *)malloc(numV*sizeof(float ));
   fn=(float *)malloc(numV*sizeof(float ));
   for(i=0; i<numV; i++)
   {
     v[i]=minV+i*dV;
     fn[i]=0.0;
   }

   in = fopen(argv[1],"r");
//      fgets(str,100,inCen);       
   while(fscanf(in,"%g %g %g %g %g",&x,&px,&py,&pz,&gamma)!=EOF) 
   {
     beta=px/gamma;
     i=(int)((beta-minV)/dV);
     if(i>=0 && i<numV)
       fn[i]+=1.0;
   }
   fclose(in);

   for(i=0; i<numV; i++)
     printf("%g %g\n",v[i],fn[i]);

   free(v);
   free(fn);

}
