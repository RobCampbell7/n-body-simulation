#ifndef NBODY_H
#define NBODY_H

typedef struct{
    double *pointX, *pointY, *pointZ;
    double *velX, *velY, *velZ;
    double *accX, *accY, *accZ;
    double *mass;
    int count;
} Bodies;

Bodies createBodies(int count);

Bodies readICfile(const char* filename);

void freeBodies(Bodies *bodies);

void computeAccelerations(Bodies *bodies, double softening);

void iterate(Bodies *bodies, double dt, double softening);

double squareSum(double x, double y, double z);

double magnitude(double x, double y, double z);

double gravitationalPE(Bodies* bodies, double softening);

double kineticEnergy(int i, Bodies* bodies);

#endif
