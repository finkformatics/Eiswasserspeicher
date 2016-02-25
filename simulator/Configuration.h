#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>

using namespace std;

class Configuration {
public:
    Configuration(const char* config_file);
    int getPort() {
        return port;
    }
    string getSecretToken() {
        return secretToken;
    }
    int getT_w() {
        return T_w;
    }
    int getT_m() {
        return T_m;
    }
    int getStep() {
        return step;
    }
    int getStartHour() {
        return startHour;
    }
    int getStartMinute() {
        return startMinute;
    }
    int getEndHour() {
        return endHour;
    }
    int getEndMinute() {
        return endMinute;
    }
    int getM_s() {
        return m_s;
    }
    int getT_l() {
        return t_l;
    }
    int getPin() {
        return pin;
    }
    int getWatt_per_pulse() {
        return watt_per_pulse;
    }
    int getP_s() {
        return P_s;
    }
    int getP_p() {
        return P_p;
    }
    double getQ() {
        return Q;
    }
    int getLogLevel() {
        return logLevel;
    }
    double getC_p() {
        return c_p;
    }
    double getR_m() {
        return r_m;
    }
    double getW_e() {
        return w_e;
    }
    bool getDebug() {
        return debug;
    }
private:
    void load(const char* config_file);
    // From ini file
    int port; // ControlServer port
    string secretToken;
    int T_w; // Gewünschte Milchtemperatur in C
    int T_m; // Eingangstemperatur der Milch in C
    int step; // Zeitschritt in min
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    int m_s; // Speichervolumen in kg
    int t_l; // Ladezeit in h
    int pin; // Pin für S0 Schnittstelle
    int watt_per_pulse; // Watt die ein einem Impuls entsprechen
    int P_s; // Leistung beim Laden
    int P_p; // Leistung beim Kühlen
    double Q; // Volumenstrom der Pumpen in l/min
    int logLevel;
    bool debug;
    // General constants
    double c_p; // Spezifische Wärmekapazität von Milch in kJ/(kg*K)
    double r_m; // Dichte von Milch in kg/l
    double w_e; // Energiedichte von Eis in kj/kg
};

#endif /* CONFIGURATION_H */

