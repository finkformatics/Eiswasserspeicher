#include "Pump.h"

#include <iostream>
#include <algorithm>

using namespace std;

Pump::Pump(Configuration* c) {
    config = c;
    Q = config->getQ();
    percent = 0;
}

double Pump::getM() {
    return Q * config->getR_m() * (double)percent / 100.0;
}

bool Pump::isOn() {
    return percent > 0;
}

void Pump::setPercent(int p) {
    percent = max(min(100, p), 0);
}