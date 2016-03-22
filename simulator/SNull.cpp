#include "SNull.h"

#ifdef __arm__
#include <wiringPi.h>
#endif
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "Logger.h"


// Standard constructor

SNull::SNull(Configuration* c) {
    config = c;
#ifdef __arm__
    wiringPiSetup();
#endif 
    _loading = false;
    _cooling = false;
#ifdef __arm__
    pinMode(config->getPin(), OUTPUT);
#endif
}

using namespace std;

void SNull::run() {
    int millis = config->getStep() * 60 * 1000;
    if (config->getDebug()) {
        millis = 10 * 1000;
    }

    while (true) {
        int P = 0;
        if (_loading) P += config->getP_s();
        if (_cooling) P += config->getP_p();

        if (P > 0) {
            int pulses = config->getWatt_per_pulse() * P;

            int sleepMs = millis / pulses - 2 * DELAY;

            pulse();
            boost::posix_time::millisec sleepTime(sleepMs);
            boost::this_thread::sleep(sleepTime);
        }
    }
}

void SNull::toggleLoading() {
    _loading = !_loading;
}

void SNull::toggleCooling() {
    _cooling = !_cooling;
}

// Send watts

void SNull::send(int watt) {
    int times = watt / config->getWatt_per_pulse();
    for (int i = 0; i < times; i++) {
        pulse();
    }
}

// Send the pulse

void SNull::pulse() {
#ifdef __arm__
    digitalWrite(config->getPin(), HIGH);
    delay(SNull::DELAY);
    digitalWrite(config->getPin(), LOW);
    delay(SNull::DELAY);
#endif
    Logger::trace("Sending pulse");
}
