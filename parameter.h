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

   float wp;
   float kp;
   
   struct _ptclList *head;

}  Parameter; 

typedef struct _PonderScat
{
   float density;
   float minX;
   float maxX;
   float minY;
   float maxY;
   float minZ;
   float maxZ;
   float lambda;
   float divisionLambda;
   float dyOverDx;
   float dzOverDx;
   float numberInCell;
   float dt;

   float Px0;
   float Py0;
   float Pz0;

}  PonderScat; 

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

void parameterSetting(Parameter *D,PonderScat *PS,Laser *L,char *input);
void boundary_PS(Parameter *D,PonderScat *PS);
void saveParticle(Parameter *D,int iteration);
void saveLaser(Parameter *D,PonderScat *PS,Laser *L,int iteration,float t);
float laser2D(float t,float x,float y,float a0,float sigmaX,float sigmaY);
void updateMomenta(Parameter *D,PonderScat *PS,Laser *L,float t);
void updatePosition(Parameter *D,PonderScat *PS,Laser *L,float t);
