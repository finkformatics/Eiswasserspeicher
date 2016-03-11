#ifndef SNULL_H
#define SNULL_H

class SNull {
	public:
		SNull(int pin, int watt_per_pulse);
		void run();
		void send(int watt); // Send the watts as pulses
		void toggleLoading();
		void toggleCooling();
		static const int DELAY = 30; // Delay for S0 interface
		
	private:
		int _pin; // pin for S0 interface
		int _watt_per_pulse; // How many watts is a pulse
		bool _loading;
		bool _cooling;
		void pulse(); // Pulse function
};

#endif
