#include "Reservoir.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::posix_time;

Reservoir::Reservoir(Configuration* c) : s0(c) {
    config = c;
    
    currentState = NONE;
    
    m_s = config->getM_s();
    t_l = config->getT_l();
    
    Q_s_max = m_s * config->getW_e();
    Q_s = 0.0;
    Q_l = Q_s_max / (t_l * 60 / config->getStep());
    
    boost::thread(boost::bind(&SNull::run, &s0));
}

void Reservoir::step() {
    if (currentState == COOLING || currentState == BOTH) {
        Logger::debug("Cooling milk");
        cool();
    } else {
           s0.coolingOff();
    }
    if (currentState == LOADING || currentState == BOTH) {
        Logger::debug("Loading reservoir");
        load();
    } else {
            s0.loadingOff();
    }

    ostringstream oss;
    oss << "Q_s = " << Q_s;
    Logger::debug(oss.str());
}

void Reservoir::toggleLoading() {
	switch(currentState) {
		case NONE: 
            currentState = LOADING; 
            break;
		case LOADING: 
            currentState = NONE; 
            break;
		case COOLING: 
            currentState = BOTH; 
            break;
		case BOTH: 
            currentState = COOLING; 
            break;
		default: 
            currentState = NONE; 
            break;
	}
}

void Reservoir::toggleCooling() {
	switch(currentState) {
		case NONE: 
            currentState = COOLING; 
            break;
		case LOADING: 
            currentState = BOTH; 
            break;
		case COOLING: 
            currentState = NONE; 
            break;
		case BOTH: 
            currentState = LOADING; 
            break;
		default: 
            currentState = NONE; 
            break;
	}
}

void Reservoir::cool() {
    double Q_w = 2 * config->getQ() * config->getR_m() * config->getC_p() * (config->getT_m() - config->getT_w()) * config->getStep();
    if (Q_w < Q_s) {
        s0.coolingOn();
        Q_s -= Q_w;
    } else {
        s0.coolingOff();
        Q_s = 0;
    }
}

void Reservoir::load() {
    if(Q_s < Q_s_max) {
       s0.loadingOn();
    } else {
       s0.loadingOff();
    }
    Q_s = (Q_s < Q_s_max - Q_l) ? Q_s + Q_l : Q_s_max;
}
