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
   float ***Ex;
   float ***Ey;
   float ***Ez;

   int Enodes;
   int Mnodes;  
   float **elec;
   float **magnet;
   float Epot;
   float Mpot;


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

 
typedef struct _Laser  {
    float sigmaX;
    float sigmaY;
    float sigmaZ;
    float a0;
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
}  Laser;     

void parameterSetting(Parameter *D,char *input);
