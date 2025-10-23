#ifndef KEYBOARDLOGGER_H
#define KEYBOARDLOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class KeyboardLogger {
private:
    std::ofstream logFile;

public:
    KeyboardLogger(const std::string& filename = "keyboard_actions.log");
    ~KeyboardLogger();
    void log(const std::string& input);
};

extern KeyboardLogger keyLogger;
void logKeyboardInput(const std::string& input);

#endif