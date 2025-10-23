#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <fstream>
#include <string>
#include "KeyboardLogger.h"

class Pipe {
private:
    int id;
    std::string name;
    float length;
    int diameter;
    bool status;

public:
    Pipe();
    Pipe(int i, std::string n, float len, int diam, bool stat);

    int getID() const;
    std::string getName() const;
    float getLength() const;
    int getDiameter() const;
    bool getStatus() const;

    void setID(const int& i);
    void setName(const std::string& n);
    void setLength(float len);
    void setDiameter(int diam);
    void setStatus(bool stat);

    void display() const;
    void toggleStatus();
    void inputFromConsole();
    void displayInfo(int index = -1) const;
    void saveToFile(std::ofstream& outFile, int index = -1) const;
};

#endif