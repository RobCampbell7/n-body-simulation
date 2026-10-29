#include <stdio.h>
#include <stdlib.h>
typedef struct{
    double *pointX, *pointY, *pointZ;
    double *velX, *velY, *velZ;
    double *accX, *accY, *accZ;
    double *mass;
    int count;
} Bodies;

static double *allocateArray(int count, const char *name);
 
Bodies createBodies(int count);

void freeBodies(Bodies *bodies);

void computeAccelerations(Bodies *bodies, double softening);

void iterate(Bodies *bodies, double dt, double softening);
