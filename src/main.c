#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"

const char* ICFILENAME = "../initConditions/initConditions.csv";
const char* OUTFILENAME = "../output/bodies.csv";

void writeToFile(FILE *fpt, double time, Bodies *bodies);

int main(){
    int iterLimit = 10000;
    int outputInterval = 100;
    double dt = 0.1;
    double softening = 0.01;

    Bodies bodies = readICfile(ICFILENAME);

    FILE *fpt = fopen(OUTFILENAME, "w");
    if (!fpt){
        perror(OUTFILENAME);
        exit(EXIT_FAILURE);
    }
    computeAccelerations(&bodies, softening);
    writeToFile(fpt, 0.0, &bodies);
    for (int i = 0; i < iterLimit; i++) {
        iterate(&bodies, dt, softening);
        if ((i + 1) % outputInterval == 0) {    
            writeToFile(fpt, dt * (i + 1), &bodies);
        }
    }
    freeBodies(&bodies);
    fclose(fpt);
    return 0;
}

void writeToFile(FILE *fpt, double time, Bodies *bodies){
    fprintf(fpt, "%.9g,%.9g,%.9g,%.9g", time, bodies->pointX[0], bodies->pointY[0], bodies->pointZ[0]);
    for (int i=1; i<bodies->count; i++){
        fprintf(fpt, ",%.9g,%.9g,%.9g", bodies->pointX[i], bodies->pointY[i], bodies->pointZ[i]);
    }
    fprintf(fpt, "\n");
}
