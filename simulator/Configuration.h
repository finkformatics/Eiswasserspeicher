#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration {
public:
    Configuration(const char* config_file);
    int getPort() {
        return port;
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
    int getM_s() {
        return m_s;
    }
    int getT_l() {
        return t_l;
    }
    double getQ() {
        return Q;
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
private:
    void load(const char* config_file);
    // From ini file
    int port; // ControlServer port
    int T_w; // Gewünschte Milchtemperatur in C
    int T_m; // Eingangstemperatur der Milch in C
    int step; // Zeitschritt in min
    int m_s; // Speichervolumen in kg
    int t_l; // Ladezeit in h
    double Q; // Volumenstrom der Pumpen in l/min
    // General constants
    double c_p; // Spezifische Wärmekapazität von Milch in kJ/(kg*K)
    double r_m; // Dichte von Milch in kg/l
    double w_e; // Energiedichte von Eis in kj/kg
};

#endif /* CONFIGURATION_H */

