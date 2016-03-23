#ifndef SNULL_H
#define SNULL_H

#include "Configuration.h"

class SNull {
public:
    SNull(Configuration* c);
    void run();
    void send(int watt); // Send the watts as pulses
    void toggleLoading();
    void toggleCooling();
    void loadingOn();
    void loadingOff();
    void coolingOn();
    void coolingOff();
    static const int DELAY = 30; // Delay for S0 interface

private:
    Configuration* config;
    bool _loading;
    bool _cooling;
    void pulse(); // Pulse function
};

#endif
