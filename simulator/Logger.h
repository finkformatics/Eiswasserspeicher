#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include "Configuration.h"

using namespace std;

class Logger {
public:
    static void init(Configuration* config);
    static void setLevel(int level) {
        Logger::level = level;
    }
    static void error(string message);
    static void warn(string message);
    static void info(string message);
    static void debug(string message);
    static void trace(string message);
private:
    static int level;
    static const int TRACE;
    static const int DEBUG;
    static const int INFO;
    static const int WARN;
    static const int ERROR;
    
    static void log(int level, string levelMsg, string message);
};

#endif /* LOGGER_H */

