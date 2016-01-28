#ifndef PUMP_H
#define PUMP_H

#include "Configuration.h"

class Pump {
public:
    Pump(Configuration* config);
    double getM();
    bool isOn();
    void on() { 
        percent = 100;
    }
    void off() {
        percent = 0;
    }
    void setPercent(int percent);
private:
    Configuration* config;
    double Q;
    int percent;
};

#endif /* PUMP_H */

