#include "SNull.h"

#ifdef __arm__
#include <wiringPi.h>
#endif
#include <iostream>
#include <boost/thread.hpp>

// Standard constructor
SNull::SNull(int pin, int watt_per_pulse) {
#ifdef __arm__
	wiringPiSetup();
#endif	
	_pin = pin;
	_watt_per_pulse = watt_per_pulse;
#ifdef __arm__
	pinMode(_pin, OUTPUT);
#endif
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
}
