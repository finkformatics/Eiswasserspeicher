#include "Reservoir.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::posix_time;

Reservoir::Reservoir(Configuration* c) : pump1(c), pump2(c), s0(c->getPin(), c->getWatt_per_pulse()) {
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
	}
	
	if (currentState == LOADING || currentState == BOTH) {
		Logger::debug("Loading reservoir");
        load();
	}
	
	if (toggleS0Loading) {
		toggleS0Loading = false;
		s0.toggleLoading();
	}
	
	if (toggleS0Cooling) {
		toggleS0Cooling = false;
		s0.toggleCooling();
	}

    ostringstream oss;
    oss << "Q_s = " << Q_s;
    Logger::debug(oss.str());
}

void Reservoir::toggleLoading() {
	switch(currentState) {
		case NONE: currentState = LOADING; break;
		case LOADING: currentState = NONE; break;
		case COOLING: currentState = BOTH; break;
		case BOTH: currentState = COOLING; break;
		default: currentState = NONE; break;
	}
	toggleS0Loading = !toggleS0Loading;
}

void Reservoir::toggleCooling() {
	switch(currentState) {
		case NONE: currentState = COOLING; break;
		case LOADING: currentState = BOTH; break;
		case COOLING: currentState = NONE; break;
		case BOTH: currentState = LOADING; break;
		default: currentState = NONE; break;
	}
	toggleS0Cooling = !toggleS0Cooling;
}

void Reservoir::cool() {
    double Q_w = (8.3 + 8.3) * config->getC_p() * (config->getT_m() - config->getT_w()) * config->getStep();
    if (Q_w < Q_s) {
        Q_s -= Q_w;
    } else {
        Q_s = 0;
    }
    //boost::thread(boost::bind(&SNull::send, &s0, config->getP_p()));
}

void Reservoir::load() {
    Q_s = (Q_s < Q_s_max - Q_l) ? Q_s + Q_l : Q_s_max;
    //boost::thread(boost::bind(&SNull::send, &s0, config->getP_s()));
}

bool Reservoir::timeToLoad() {
    ptime now = second_clock::local_time();
    int currentHour = now.time_of_day().hours();
    int currentMinute = now.time_of_day().minutes();
    return currentHour >= config->getStartHour() 
            && (currentMinute >= config->getStartMinute() || currentHour != config->getStartHour())
            && currentHour <= config->getEndHour() 
            && (currentMinute <= config->getEndMinute() || currentHour < config->getEndHour());
}
