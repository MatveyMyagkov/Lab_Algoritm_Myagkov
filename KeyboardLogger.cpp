#include "KeyboardLogger.h"

KeyboardLogger keyLogger;

KeyboardLogger::KeyboardLogger(const std::string& filename) {
    logFile.open(filename);
    if (!logFile.is_open()) {
        std::cerr << "Cannot open log file!" << std::endl;
    }
}

KeyboardLogger::~KeyboardLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void KeyboardLogger::log(const std::string& input) {
    if (logFile.is_open() && !input.empty()) {
        logFile << input << std::endl;
        logFile.flush();
    }
}

void logKeyboardInput(const std::string& input) {
    keyLogger.log(input);
}