#include "SNull.h"

#ifdef __arm__
#include <wiringPi.h>
#endif
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>


// Standard constructor
SNull::SNull(int pin, int watt_per_pulse) {
#ifdef __arm__
	wiringPiSetup();
#endif	
	_pin = pin;
	_watt_per_pulse = watt_per_pulse;
	_loading = false;
	_cooling = false;
#ifdef __arm__
	pinMode(_pin, OUTPUT);
#endif
}

using namespace std;

void SNull::run() {
	int P_p = 500;
	int P_s = 3570;
	int pulse_kw = 1000;
	int pulse_w = 1;
	int stepDuration = 15 * 60 * 1000; // in millisec

	while(true) {
		int P = 0;
		if (_loading) P += P_s;
		if (_cooling) P += P_p;
		
		if (P > 0) {
			int pulses = pulse_w * P;
		
			int sleepMs = stepDuration / pulses - 2 * DELAY;
			
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
	int times = watt / _watt_per_pulse;
	for(int i = 0; i < times; i++) {
		pulse();
	}
}

// Send the pulse
void SNull::pulse() {
#ifdef __arm__
	digitalWrite(_pin, HIGH);
	delay(SNull::DELAY);
	digitalWrite(_pin, LOW);
	delay(SNull::DELAY);
#endif
	cout << "Sending pulse" << endl;
}
