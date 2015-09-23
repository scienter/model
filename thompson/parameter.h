//#include "particle.h"
//#include "laser.h"
//#include "plasma.h"

#define PonderoScat 	1
#define SECOND 	2
#define THIRD 	3

#define ON	1
#define OFF	0

#define TXT	0
#define HDF	1

typedef struct _Parameter
{
   int dimension;
   int mode;
   
   int saveStart;
   int saveStep;
   int finalStep;

   int nx;
   int ny;
   float dx;
   float dy;
   float minX;
   float maxX;
   float minY;
   float maxY;
   float ***V;
   float ***M;

   struct _LoadList *EloadList;
   struct _LoadList *MloadList;
   struct _ptclList *head;

}  Parameter; 

 
typedef struct _ptclList  {
    float x;
    float oldX;
    float y;
    float oldY;
    float z;
    float oldZ;
    float Px;
    float oldPx;
    float Py;
    float oldPy;
    float Pz;
    float oldPz;
    int index;
    struct _ptclList *next;
}  ptclList;    

 
typedef struct _LoadList  {
   int nodes;
   float **points;
   float pot;
   struct _LoadList *next;
   
}  LoadList;     

void parameterSetting(Parameter *D,char *input);
void boundary(Parameter *D);
void saveField(Parameter *D,int iteration);
