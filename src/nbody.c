#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"

static double *allocateArray(int count, const char *name) {
    double *array = calloc(count, sizeof(double));
    if (!array) {
        fprintf(stderr, "memory allocation on %s failed\n", name);
        exit(EXIT_FAILURE);
    }
    return array;
}
 
Bodies createBodies(int count) {
    Bodies bodies;
    bodies.pointX = allocateArray(count, "pointX");
    bodies.pointY = allocateArray(count, "pointY");
    bodies.pointZ = allocateArray(count, "pointZ");
    bodies.velX = allocateArray(count, "velX");
    bodies.velY = allocateArray(count, "velY");
    bodies.velZ = allocateArray(count, "velZ");
    bodies.accX = allocateArray(count, "accX");
    bodies.accY = allocateArray(count, "accY");
    bodies.accZ = allocateArray(count, "accZ");
    bodies.mass = allocateArray(count, "mass");
    bodies.count = count;
    return bodies;
}

void freeBodies(Bodies *bodies) {
    free(bodies->pointX);
    free(bodies->pointY);
    free(bodies->pointZ);
    free(bodies->velX);
    free(bodies->velY);
    free(bodies->velZ);
    free(bodies->accX);
    free(bodies->accY);
    free(bodies->accZ);
    free(bodies->mass);

    bodies->pointX = bodies->pointY = bodies->pointZ = NULL;
    bodies->velX = bodies->velY = bodies->velZ = NULL;
    bodies->accX = bodies->accY = bodies->accZ = NULL;
    bodies->mass = NULL;
    bodies->count = 0;
}

void computeAccelerations(Bodies *bodies, double softening){
    return ;
}

void iterate(Bodies *bodies, double dt, double softening) {
    return ;
}
