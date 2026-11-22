#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"

const char* ICFILENAME = "../initConditions/initConditions.csv";
const char* POSITIONFILENAME = "../output/bodyPositions.csv";
const char* ENERGYFILENAME = "../output/bodyEnergies.csv";

void writeToPositionFile(FILE *fpt, double time, Bodies *bodies);

void writeToEnergyFile(FILE *fpt, double time, int count, double gpe, double* ke);

int main(){
    int iterLimit = 10000;
    int outputInterval = 100;
    double dt = 0.1;
    double softening = 0.01;

    
    FILE *posfpt = fopen(POSITIONFILENAME, "w");
    FILE *nrgfpt = fopen(ENERGYFILENAME, "w");
    if (!posfpt){
        perror(POSITIONFILENAME);
        exit(EXIT_FAILURE);
    }
    if (!nrgfpt){
        perror(ENERGYFILENAME);
        exit(EXIT_FAILURE);
    }

    Bodies bodies = readICfile(ICFILENAME);
    double ke[bodies.count];
    double gpe;

    computeAccelerations(&bodies, softening);
    writeToPositionFile(posfpt, 0.0, &bodies);

    gpe = gravitationalPE(&bodies, softening);
    for (int j=0; j<bodies.count; j++){
        ke[j] = kineticEnergy(j, &bodies);
    }
    writeToEnergyFile(nrgfpt, 0.0, bodies.count, gpe, ke);

    for (int i = 0; i < iterLimit; i++) {
        iterate(&bodies, dt, softening);

        if ((i + 1) % outputInterval == 0) {    
            writeToPositionFile(posfpt, dt * (i + 1), &bodies);
            gpe = gravitationalPE(&bodies, softening);
            for (int j=0; j<bodies.count; j++){
                ke[j] = kineticEnergy(j, &bodies);
            }
            writeToEnergyFile(nrgfpt, dt * (i + 1), bodies.count, gpe, ke);
        }
    }
    freeBodies(&bodies);
    fclose(posfpt);
    fclose(nrgfpt);
    return 0;
}

void writeToPositionFile(FILE *fpt, double time, Bodies *bodies){
    fprintf(fpt, "%.9g", time);
    for (int i=0; i<bodies->count; i++){
        fprintf(fpt, ",%.9g,%.9g,%.9g", bodies->pointX[i], bodies->pointY[i], bodies->pointZ[i]);
    }
    fprintf(fpt, "\n");
}

void writeToEnergyFile(FILE *fpt, double time, int count, double gpe, double* ke){
    fprintf(fpt, "%.9g,%.9g", time, gpe);
    for (int i=0; i<count; i++){
        fprintf(fpt, ",%.9g", ke[i]);
    }
    fprintf(fpt, "\n");
}
