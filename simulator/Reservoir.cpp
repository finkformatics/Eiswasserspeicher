#include "Reservoir.h"
#include "Logger.h"

#include <iostream>
#include <sstream>

using namespace std;

Reservoir::Reservoir(Configuration* c) : pump1(c), pump2(c), s0(c->getPin(), c->getWatt_per_pulse()) {
    config = c;
    
    m_s = config->getM_s();
    t_l = config->getT_l();
    
    Q_s_max = m_s * config->getW_e();
    Q_s = 0.0;
    Q_l = Q_s_max / (t_l * 60 / config->getStep());
}

void Reservoir::step() {
    if ((pump1.isOn() || pump2.isOn()) && Q_s > 0) {
        Logger::debug("Cooling milk");
        cool();
    } else if(Q_s < Q_s_max) { // TODO: Zeitsteuerung (12 - 16 Uhr)
        Logger::debug("Loading reservoir");
        load();
    }
    ostringstream oss;
    oss << "Q_s = " << Q_s;
    Logger::debug(oss.str());
}

void Reservoir::enablePumps() {
    pump1.on();
    pump2.on();
    Logger::info("Enabled pumps");
}

void Reservoir::disablePumps() {
    pump1.off();
    pump2.off();
    Logger::info("Disabled pumps");
}

void Reservoir::cool() {
    double Q_w = (pump1.getM() + pump2.getM()) * config->getC_p() * (config->getT_m() - config->getT_w()) * config->getStep();
    if (Q_w < Q_s) {
        Q_s -= Q_w;
    } else {
        Q_s = 0;
    }
    s0.send(config->getP_p());
}

void Reservoir::load() {
    Q_s = (Q_s < Q_s_max - Q_l) ? Q_s + Q_l : Q_s_max;
    s0.send(config->getP_s());
}
