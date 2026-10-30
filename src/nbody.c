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

double G = 6.674 * 10**-11

void computeAccelerations(Bodies *bodies, double softening) {
    double soft2 = softening * softening;
    for (int i = 0; i < bodies->count; i++) {
        double sumX = 0.0, sumY = 0.0, sumZ = 0.0;
        for (int j = 0; j < bodies->count; j++) {
            if (i == j) continue;
            double dx = bodies->pointX[j] - bodies->pointX[i];
            double dy = bodies->pointY[j] - bodies->pointY[i];
            double dz = bodies->pointZ[j] - bodies->pointZ[i];
            double r2 = dx*dx + dy*dy + dz*dz + soft2;
            double invR3 = 1.0 / (r2 * sqrt(r2));
            sumX += bodies->mass[j] * dx * invR3;
            sumY += bodies->mass[j] * dy * invR3;
            sumZ += bodies->mass[j] * dz * invR3;
        }
        bodies->accX[i] = G * sumX;
        bodies->accY[i] = G * sumY;
        bodies->accZ[i] = G * sumZ;
    }
}

void iterate(Bodies *bodies, double dt, double softening) {
    double halfDt = 0.5 * dt;

    for (int i = 0; i < bodies->count; i++) {
        bodies->velX[i] += bodies->accX[i] * halfDt;
        bodies->velY[i] += bodies->accY[i] * halfDt;
        bodies->velZ[i] += bodies->accZ[i] * halfDt;
        bodies->pointX[i] += bodies->velX[i] * dt;
        bodies->pointY[i] += bodies->velY[i] * dt;
        bodies->pointZ[i] += bodies->velZ[i] * dt;
    }

    computeAccelerations(bodies, softening);

    for (int i = 0; i < bodies->count; i++) {
        bodies->velX[i] += bodies->accX[i] * halfDt;
        bodies->velY[i] += bodies->accY[i] * halfDt;
        bodies->velZ[i] += bodies->accZ[i] * halfDt;
    }
}
