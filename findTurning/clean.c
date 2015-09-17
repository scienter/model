#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "constants.h"
#include <math.h>

void cleanMemory(Parameter *D)
{
   ptclList *p,*tmp; 

    //remove particles
    if(D->dimension==2)
    {
      p=D->head;
      while(p)
      {	
        tmp=p->next;
        D->head=tmp; 
        p->next=NULL;
        free(p);
        p=D->head;
      }
    }		
}
