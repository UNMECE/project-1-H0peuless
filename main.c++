#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct _capacitor
{
    double *time;       // time array
    double *voltage;    // voltage array
    double *current;    // current array
    double C;           // capacitance value
};
typedef struct _capacitor Capacitor;

Capacitor createCapacitor(float dt, float finalTime, double capacitance) {
    Capacitor cap;
    int size = finalTime/dt;
    // Allocation de mémoire pour les tableaux
    cap.time = (double *)malloc(size * sizeof(double));
    cap.voltage = (double *)malloc(size * sizeof(double));
    cap.current = (double *)malloc(size * sizeof(double));

    // Vérification de l'allocation
    if (cap.time == NULL || cap.voltage == NULL || cap.current == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    cap.time[0] = 0;
    for(int i = 1; i < size; i++) {
        cap.time[i] = cap.time[i-1] + dt;
    }
    cap.C = capacitance;
    return cap;
}


void computeVoltage(Capacitor* capacitor,float V0, float I0, int time) {
    capacitor->voltage[0] = 0;
    capacitor->current[1] = I0;
    double dt = capacitor->time[1] - capacitor->time[0];

    for(int i = 1; i < time; i++){
        capacitor->voltage[i] = capacitor->voltage[i-1] + capacitor->current[i-1]*dt*(1/capacitor->C);
    }
}

void computeCurrent(Capacitor* capacitor,float V0, float I0, float R, int time) {
    capacitor->voltage[0] = V0;
    capacitor->current[0] = I0;
    double dt = capacitor->time[1] - capacitor->time[0];
    for(int i = 1; i < time; i++) {
        capacitor->current[i] = capacitor->current[i-1] - (capacitor->current[i-1]/(R*capacitor->C))*dt;
    }

}

void printCapacitor(Capacitor* capacitor,int time){
    for(int i = 0; i < time; i+=200) {
        cout << capacitor->time[i] << " " << capacitor->voltage[i] << " " << capacitor->current[i] << endl;
    }
}




int main(int argc, char *argv[]) {
    const double C = 100e-12;
    const float R = 1000;
    const float V0 = 10;
    const float I0 = 1e-2;
    const float finalTime = 5e-6;
    const float dt = 1e-10;
    const int time = int(finalTime/dt);

    Capacitor C1 = createCapacitor(dt,finalTime, C);

    computeCurrent(&C1,V0,I0,R,time);
    computeVoltage(&C1,V0,I0,time);
    printCapacitor(&C1,time);

    return 0;
};
