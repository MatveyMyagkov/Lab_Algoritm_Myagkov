#include "Pipe.h"

Pipe::Pipe() : id(0), name(""), length(0.0f), diameter(0), status(false) {}

Pipe::Pipe(int i, std::string n, float len, int diam, bool stat)
    : id(i), name(n), length(len), diameter(diam), status(stat) {
}

int Pipe::getID() const { return id; }
std::string Pipe::getName() const { return name; }
float Pipe::getLength() const { return length; }
int Pipe::getDiameter() const { return diameter; }
bool Pipe::getStatus() const { return status; }

void Pipe::display() const { std::cout << "�����: " << name << " (ID: " << id << ")" << std::endl; }

void Pipe::setID(const int& i) { id = i; }

void Pipe::setName(const std::string& n) {
    if (!n.empty() || n.find_first_not_of(' ') == std::string::npos) {
        name = n;
    }
}

void Pipe::setLength(float len) {
    if (len > 0) {
        length = len;
    }
}

void Pipe::setDiameter(int diam) {
    if (diam > 0) {
        diameter = diam;
    }
}

void Pipe::setStatus(bool stat) { status = stat; }

void Pipe::toggleStatus() { status = !status; }

void Pipe::inputFromConsole() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "������� ������������ ������� (�������� �����): ";
    std::string name_input;
    std::getline(std::cin, name_input);
    logKeyboardInput(name_input);
    setName(name_input);

    while (name.empty() || name.find_first_not_of(' ') == std::string::npos) {
        std::cout << "������! �������� �� ����� ���� ������. ������� �����: ";
        std::getline(std::cin, name);
        logKeyboardInput(name);
    }

    std::cout << "������� ����� ����� (��): ";
    float length;
    while (!(std::cin >> length) || length <= 0 || std::cin.peek() != '\n') {
        std::cout << "������! ������� ������������� �����: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(length));
    }
    logKeyboardInput(std::to_string(length));
    setLength(length);

    std::cout << "������� ������� ����� (��): ";
    int diameter;
    while (!(std::cin >> diameter) || diameter <= 0 || std::cin.peek() != '\n') {
        std::cout << "������! ������� ������������� ����� �����: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(diameter));
    }
    logKeyboardInput(std::to_string(diameter));
    setDiameter(diameter);

    std::cout << "����� � �������? (1 - ��, 0 - ���): ";
    int repairStatus;
    while (!(std::cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1) || std::cin.peek() != '\n') {
        std::cout << "������! ������� 0 ��� 1: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(repairStatus));
    }
    status = (repairStatus == 1);
    logKeyboardInput(std::to_string(repairStatus));
    std::cin.ignore(1000, '\n');
}

void Pipe::displayInfo(int index) const {
    if (index != -1) {
        std::cout << "����� #" << (index + 1) << std::endl;
    }
    std::cout << "  (ID: " << id << ")" << std::endl;
    std::cout << "  ��������: " << name << std::endl;
    std::cout << "  �����: " << length << " ��" << std::endl;
    std::cout << "  �������: " << diameter << " ��" << std::endl;
    std::cout << "  ������: " << (status ? "� �������" : "��������") << std::endl;
    std::cout << std::endl;
}

void Pipe::saveToFile(std::ofstream& outFile, int index) const {
    if (index != -1) {
        outFile << "����� #" << (index + 1) << std::endl;
    }
    outFile << "  ID: " << id << std::endl;
    outFile << "  Name: " << name << std::endl;
    outFile << "  Length: " << length << " km" << std::endl;
    outFile << "  Diameter: " << diameter << " mm" << std::endl;
    outFile << "  Status: " << (status ? "Not worked" : "Worked") << std::endl;
    outFile << std::endl;
}