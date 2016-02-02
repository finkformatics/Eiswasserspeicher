#include "Configuration.h"

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace po = boost::program_options;

Configuration::Configuration(const char* config_file) {
    load(config_file);
    c_p = 3.85;
    r_m = 1.02;
    w_e = 333;
}

void Configuration::load(const char* config_file) {
    cout << "Reading configuration" << endl;
    po::options_description desc("Parameters");
    desc.add_options()
        ("controlserver.port", po::value<int>(&port), "server port")
        ("milk.temp.target", po::value<int>(&T_w), "target temp milk")
        ("milk.temp.input", po::value<int>(&T_m), "input temp milk")
        ("simulator.time.step", po::value<int>(&step), "input temp milk")
        ("snull.pin", po::value<int>(&pin), "snull pin")
        ("snull.watt.per.pulse", po::value<int>(&watt_per_pulse), "snull watt per pulse")
        ("snull.watt.per.load", po::value<int>(&P_s), "snull watt per load")
        ("snull.watt.per.cool", po::value<int>(&P_p), "snull watt per cool")
        ("reservoir.capacity", po::value<int>(&m_s), "reservoir capacity")
        ("reservoir.loadingtime", po::value<int>(&t_l), "reservoir loading time")
        ("reservoir.pumps.flow", po::value<double>(&Q), "pumps volume flow");
    po::variables_map vm;
    std::ifstream file(config_file, std::ifstream::in);
    cout << "Reading program parameters" << endl;
    po::store(po::parse_config_file(file, desc), vm);
    file.close();
    po::notify(vm);
}
