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
    int size = finalTime/dt; // Size of the arrays
    // Table memory allocation
    cap.time = (double *)malloc(size * sizeof(double));    // Time array
    cap.voltage = (double *)malloc(size * sizeof(double)); // Voltage array
    cap.current = (double *)malloc(size * sizeof(double)); // Current array

    // Memory allocation check
    if (cap.time == NULL || cap.voltage == NULL || cap.current == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    cap.time[0] = 0; // Initial value for the time array
    for(int i = 1; i < size; i++){
        cap.time[i] = cap.time[i-1] + dt; // Add a new instant
    }
    cap.C = capacitance; // Capacitance
    return cap;
}


void computeVoltage(Capacitor* capacitor,float V0, float I0, int time) { //Compute the current if the voltage is constant
    capacitor->voltage[0] = 0;
    capacitor->current[1] = I0;
    double dt = capacitor->time[1] - capacitor->time[0];

    for(int i = 1; i < time; i++){
        capacitor->voltage[i] = capacitor->voltage[i-1] + capacitor->current[i-1]*dt*(1/capacitor->C);
    }
}

void computeCurrent(Capacitor* capacitor,float V0, float I0, float R, int time) { //Compute the current if the voltage is constant
    capacitor->voltage[0] = V0;
    capacitor->current[0] = 0;
    double dt = capacitor->time[1] - capacitor->time[0];
    for(int i = 1; i < time; i++) {
        capacitor->current[i] = capacitor->current[i-1] - (capacitor->current[i-1]/(R*capacitor->C))*dt;
    }

}

void printCapacitor(Capacitor* capacitor,int time){
    for(int i = 0; i < time; i+=200) { //Every 200 stps print the values
        cout << setw(8) << left <<  capacitor->time[i] << " | "<<  setw(8) << left << capacitor->voltage[i] << " | "<<  setw(8) << left << capacitor->current[i] << endl; //Format the output string as a table
    }
}




int main(int argc, char *argv[]) {
    const double C = 100e-12; // Capacitance
    const float R = 1000;     // Resistance in circuit 2
    const float V0 = 10;      // Voltage in constant voltage circuit
    const float I0 = 1e-2;    // Current in constant current circuit
    const float finalTime = 5e-6;
    const float dt = 1e-10;
    const int time = int(finalTime/dt);

    Capacitor C1 = createCapacitor(dt,finalTime, C);

    computeCurrent(&C1,V0,I0,R,time); //Compute the current
    computeVoltage(&C1,V0,I0,time);   //Compute the voltage
    printCapacitor(&C1,time);         //print method every 200 steps

    return 0;
};
