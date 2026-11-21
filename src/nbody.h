
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
