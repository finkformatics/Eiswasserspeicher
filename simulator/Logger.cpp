#include "Logger.h"
#include "Configuration.h"

#include <iostream>
#include <ctime>

const int Logger::ERROR = 10;
const int Logger::WARN = 20;
const int Logger::INFO = 30;
const int Logger::DEBUG = 40;

int Logger::level = 30;

void Logger::init(Configuration* config) {
    level = config->getLogLevel();
}

void Logger::error(string message) {
    log(ERROR, "ERROR", message);
}

void Logger::warn(string message) {
    log(WARN, "WARNING", message);
}

void Logger::info(string message) {
    log(INFO, "INFO", message);
}

void Logger::debug(string message) {
    log(DEBUG, "DEBUG", message);
}

void Logger::log(int level, string levelMsg, string message) {
    if (level <= Logger::level) {
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        string str(buffer);

        cout << str << " " << levelMsg << " " << message << endl;
    }
}