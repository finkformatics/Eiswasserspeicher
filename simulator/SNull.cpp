#include "SNull.h"

#include <wiringPi.h>
#include <iostream>

// Standard constructor
SNull::SNull(int pin, int watt_per_pulse) {
	wiringPiSetup();	
	_pin = pin;
	_watt_per_pulse = watt_per_pulse;
	
	pinMode(_pin, OUTPUT);
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
	digitalWrite(_pin, HIGH);
	delay(SNull::DELAY);
	digitalWrite(_pin, LOW);
	delay(SNull::DELAY);
}
