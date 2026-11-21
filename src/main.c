#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"

char* filename = "../output/bodies.csv";

void appendToFile();

void emptyOutputFile();

int main(){
    int count = 2;
    int iterLimit = 100000;

    Bodies bodies = createBodies(count);

    bodies.pointX[0] = 1;
    bodies.pointY[0] = 1;
    bodies.pointZ[0] = 1;
    bodies.mass[0] = 1;
    bodies.velX[0] = 0;

    bodies.pointX[1] = 0;
    bodies.pointY[1] = 0;
    bodies.pointZ[1] = 0;
    bodies.mass[1] = 100;

    for (int i = 0; i < iterLimit; i++) {
        iterate(&bodies, 0.5, 0.01);
    }
    freeBodies(&bodies);
    return 0;
}

void appendToFile(Bodies bodies){
    FILE *fpt;
    fpt = fopen(filename, "a");
    if (!fpt) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    fprintf(fpt, "%lf,%lf,%lf", bodies.pointX[0], bodies.pointY[0], bodies.pointZ[0]);
    for (int i=1; i<bodies.count; i++){
        fprintf(fpt, ",%lf,%lf,%lf", bodies.pointX[i], bodies.pointY[i], bodies.pointZ[i]);
    }
    fprintf(fpt, "\n");
    fclose(fpt);
}
void emptyOutputFile(){
    FILE *fpt;
    fpt = fopen(filename, "w");
    if (!fpt) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    //fprintf(fpt, "");
    fclose(fpt);
}
