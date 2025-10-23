#include "CS.h"

CS::CS() : id(0), name(""), number_work(0), number_work_online(0), class_cs("") {}

CS::CS(int i, std::string n, int num_work, int num_online, std::string cls)
    : id(i), name(n), number_work(num_work), number_work_online(num_online), class_cs(cls) {
}

int CS::getID() const { return id; }
std::string CS::getName() const { return name; }
int CS::getNumberWork() const { return number_work; }
int CS::getNumberWorkOnline() const { return number_work_online; }
std::string CS::getClassCS() const { return class_cs; }

void CS::display() const { std::cout << "��: " << name << " (ID: " << id << ")" << std::endl; }

void CS::setID(const int& i) { id = i; }

void CS::setName(const std::string& n) {
    if (!n.empty() || n.find_first_not_of(' ') == std::string::npos) {
        name = n;
    }
}

void CS::setNumberWork(int num) {
    if (num > 0) {
        number_work = num;
    }
}

void CS::setNumberWorkOnline(int num) {
    if (num >= 0 && num <= number_work) {
        number_work_online = num;
    }
}

void CS::setClassCS(const std::string& cls) {
    if (!cls.empty()) {
        class_cs = cls;
    }
}

void CS::startWorkshop() {
    if (number_work_online < number_work) {
        number_work_online++;
    }
}

void CS::stopWorkshop() {
    if (number_work_online > 0) {
        number_work_online--;
    }
}

void CS::inputFromConsole() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "������� �������� ��: ";
    std::string name_input;
    std::getline(std::cin, name_input);
    setName(name_input);

    while (name.empty() || name.find_first_not_of(' ') == std::string::npos) {
        std::cout << "������! �������� �� ����� ���� ������. ������� �����: ";
        std::getline(std::cin, name);
        logKeyboardInput(name_input);
    }
    logKeyboardInput(name_input);

    std::cout << "������� ���������� �����: ";
    int number_work;
    while (!(std::cin >> number_work) || number_work <= 0 || std::cin.peek() != '\n') {
        std::cout << "������! ������� ������������� ����� �����: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(number_work));
    }
    logKeyboardInput(std::to_string(number_work));
    setNumberWork(number_work);

    std::cout << "������� ���������� ���������� �����: ";
    int number_work_online;
    while (!(std::cin >> number_work_online) || number_work_online < 0 ||
        number_work_online > number_work || std::cin.peek() != '\n') {
        if (std::cin.fail()) {
            std::cout << "������! ������� ����� �����: ";
        }
        else if (number_work_online > number_work) {
            std::cout << "������! ���������� ���� �� ����� ��������� ����� ���������� ����� ("
                << number_work << "). ������� �����: ";
        }
        else {
            std::cout << "������! ������� ��������������� �����: ";
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(number_work_online));
    }
    logKeyboardInput(std::to_string(number_work_online));
    setNumberWorkOnline(number_work_online);

    std::cin.ignore(1000, '\n');

    std::cout << "������� ����� �������: ";
    std::string class_input;
    std::getline(std::cin, class_input);
    setClassCS(class_input);

    while (class_cs.empty()) {
        std::cout << "������! ����� ������� �� ����� ���� ������. ������� �����: ";
        std::getline(std::cin, class_cs);
        logKeyboardInput(class_cs);
    }
    logKeyboardInput(class_cs);
}

void CS::displayInfo(int index) const {
    if (index != -1) {
        std::cout << "�� #" << (index + 1) << std::endl;
    }
    std::cout << "  (ID: " << id << ")" << std::endl;
    std::cout << "  ��������: " << name << std::endl;
    std::cout << "  ����� �����: " << number_work << std::endl;
    std::cout << "  ����� ������: " << number_work_online << std::endl;
    std::cout << "  �����: " << class_cs << std::endl;
    std::cout << std::endl;
}

void CS::saveToFile(std::ofstream& outFile, int index) const {
    if (index != -1) {
        outFile << "�� #" << (index + 1) << std::endl;
    }
    outFile << "  ID: " << id << std::endl;
    outFile << "  Name: " << name << std::endl;
    outFile << "  all workshop: " << number_work << std::endl;
    outFile << "  Online workshop: " << number_work_online << std::endl;
    outFile << "  Class: " << class_cs << std::endl;
    outFile << std::endl;
}