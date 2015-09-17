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
   int finalStep;
   int saveStep;
   int totalCnt;
   float x0;
   float rangeX;
   float dt;
   float density;
   float temperature;
   
   float wp;
   float kp;
   
   struct _ptclList *head;

}  Parameter; 

typedef struct _ptclList  {
    float x;
    float y;
    float z;
    float px;
    float py;
    float pz;
    int index;
    struct _ptclList *next;
}  ptclList;    

void saveFile(Parameter *D,int iteration);
void updatePx_X(Parameter *D);
void cleanMemory(Parameter *D);
float Efield(float x,float density);
