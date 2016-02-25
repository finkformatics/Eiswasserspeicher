#ifndef RESERVOIR_H
#define RESERVOIR_H

#include "Configuration.h"
#include "Pump.h"
#include "SNull.h"

class Reservoir {
public:
    Reservoir(Configuration* config);
    void step();
    void enablePumps();
    void disablePumps();
private:
    Configuration* config;
    Pump pump1;
    Pump pump2;
    SNull s0;
    int m_s;
    int t_l;
    int Q_s_max;
    double Q_s;
    double Q_l;
    
    void load();
    void cool();
    bool timeToLoad();
};

#endif /* RESERVOIR_H */

