#ifndef CS_H
#define CS_H

#include <iostream>
#include <fstream>
#include <string>
#include "KeyboardLogger.h"

class CS {
private:
    int id;
    std::string name;
    int number_work;
    int number_work_online;
    std::string class_cs;

public:
    CS();
    CS(int i, std::string n, int num_work, int num_online, std::string cls);

    int getID() const;
    std::string getName() const;
    int getNumberWork() const;
    int getNumberWorkOnline() const;
    std::string getClassCS() const;

    void setID(const int& i);
    void setName(const std::string& n);
    void setNumberWork(int num);
    void setNumberWorkOnline(int num);
    void setClassCS(const std::string& cls);

    void display() const;
    void startWorkshop();
    void stopWorkshop();
    void inputFromConsole();
    void displayInfo(int index = -1) const;
    void saveToFile(std::ofstream& outFile, int index = -1) const;
};

#endif
