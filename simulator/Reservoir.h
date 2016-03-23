#ifndef RESERVOIR_H
#define RESERVOIR_H

#include "Configuration.h"
#include "SNull.h"



class Reservoir {
public:
    Reservoir(Configuration* config);
    void step();
	void toggleLoading();
	void toggleCooling();
    enum State {
		NONE,
		COOLING,
		LOADING,
		BOTH
	};


private:
    Configuration* config;
    SNull s0;
    State currentState;
    int m_s;
    int t_l;
    int Q_s_max;
    double Q_s;
    double Q_l;
    
    void load();
    void cool();
};

#endif /* RESERVOIR_H */

