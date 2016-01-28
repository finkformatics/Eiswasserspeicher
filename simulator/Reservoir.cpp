#include "Reservoir.h"

#include <iostream>

using namespace std;

Reservoir::Reservoir(Configuration* c) : pump1(c), pump2(c) {
    config = c;
    
    m_s = config->getM_s();
    t_l = config->getT_l();
    
    Q_s_max = m_s * config->getW_e();
    Q_s = 0.0;
    // TODO: So richtig?
    Q_l = Q_s_max / (t_l * 60 / config->getStep());
}

void Reservoir::step() {
    if ((pump1.isOn() || pump2.isOn()) && Q_s > 0) {
        cout << "Pump on, let's cool" << endl;
        cool();
    } else if(Q_s < Q_s_max) {
        cout << "Loading cooler" << endl;
        load();
    }
}

void Reservoir::cool() {
    double Q_w = (pump1.getM() + pump2.getM()) * config->getC_p() * (config->getT_m() - config->getT_w()) * config->getStep();
    if (Q_w < Q_s) {
        Q_s -= Q_w;
    } else {
        Q_s = 0;
    }
}

void Reservoir::load() {
    Q_s = (Q_s < Q_s_max - Q_l) ? Q_s + Q_l : Q_s_max;
}
