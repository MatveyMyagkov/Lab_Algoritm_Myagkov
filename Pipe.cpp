#include "Pipe.h"
#include "Network.h"
Pipe::Pipe() : id(0), name(""), length(0.0f), diameter(0), status(false) {}

Pipe::Pipe(int i, std::string n, float len, int diam, bool stat)
    : id(i), name(n), length(len), diameter(diam), status(stat) {
}

int Pipe::getID() const { return id; }
std::string Pipe::getName() const { return name; }
float Pipe::getLength() const { return length; }
int Pipe::getDiameter() const { return diameter; }
bool Pipe::getStatus() const { return status; }

void Pipe::display() const { std::cout << "Труба: " << name << " (ID: " << id << ")" << std::endl; }

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

    std::cout << "Введите километровую отметку (Название трубы): ";
    std::string name_input;
    std::getline(std::cin, name_input);
    logKeyboardInput(name_input);
    setName(name_input);

    while (name.empty() || name.find_first_not_of(' ') == std::string::npos) {
        std::cout << "Ошибка! Название не может быть пустым. Введите снова: ";
        std::getline(std::cin, name);
        logKeyboardInput(name);
    }

    std::cout << "Введите длину трубы (км): ";
    float length;
    while (!(std::cin >> length) || length <= 0 || std::cin.peek() != '\n') {
        std::cout << "Ошибка! Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(length));
    }
    logKeyboardInput(std::to_string(length));
    setLength(length);

    const std::vector<int> allowedDiameters = { 500, 700, 1000, 1400 };

    std::cout << "Введите диаметр трубы (мм). Допустимые значения: ";
    for (size_t i = 0; i < allowedDiameters.size(); i++) {
        std::cout << allowedDiameters[i];
        if (i < allowedDiameters.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ": ";

    int diameter;
    while (!(std::cin >> diameter) || diameter <= 0 || std::cin.peek() != '\n' ||
        std::find(allowedDiameters.begin(), allowedDiameters.end(), diameter) == allowedDiameters.end()) {
        std::cout << "Ошибка! Введите один из допустимых диаметров: ";
        for (int d : allowedDiameters) std::cout << d << " ";
        std::cout << "мм: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(diameter));
    }
    logKeyboardInput(std::to_string(diameter));
    setDiameter(diameter);

    std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    int repairStatus;
    while (!(std::cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1) || std::cin.peek() != '\n') {
        std::cout << "Ошибка! Введите 0 или 1: ";
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
        std::cout << "Труба #" << (index + 1) << std::endl;
    }
    std::cout << "  (ID: " << id << ")" << std::endl;
    std::cout << "  Название: " << name << std::endl;
    std::cout << "  Длина: " << length << " км" << std::endl;
    std::cout << "  Диаметр: " << diameter << " мм" << std::endl;
    std::cout << "  Статус: " << (status ? "В ремонте" : "Работает") << std::endl;
    std::cout << std::endl;
}

void Pipe::saveToFile(std::ofstream& outFile, int index) const {
    if (index != -1) {
        outFile << "Труба #" << (index + 1) << std::endl;
    }
    outFile << "  ID: " << id << std::endl;
    outFile << "  Name: " << name << std::endl;
    outFile << "  Length: " << length << " km" << std::endl;
    outFile << "  Diameter: " << diameter << " mm" << std::endl;
    outFile << "  Status: " << (status ? "Not worked" : "Worked") << std::endl;
    outFile << std::endl;
}