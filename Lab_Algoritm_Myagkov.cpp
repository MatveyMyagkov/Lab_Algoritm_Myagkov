#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

class Pipe {
private:
    string name;
    float length;
    int diameter;
    bool status;

public:
    Pipe() : name(""), length(0.0f), diameter(0), status(false) {}

    Pipe(string n, float len, int diam, bool stat)
        : name(n), length(len), diameter(diam), status(stat) {
    }

    string getName() const { return name; }
    float getLength() const { return length; }
    int getDiameter() const { return diameter; }
    bool getStatus() const { return status; }

    void setName(const string& n) {
        if (!n.empty() || n.find_first_not_of(' ') == string::npos) {
            name = n;
        }
    }

    void setLength(float len) {
        if (len > 0) {
            length = len;
        }
    }

    void setDiameter(int diam) {
        if (diam > 0) {
            diameter = diam;
        }
    }

    void setStatus(bool stat) {
        status = stat;
    }

    void toggleStatus() {
        status = !status;
    }

    void inputFromConsole() {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Введите километровую отметку (Название трубы): ";
        getline(cin, name);

        while (name.empty() || name.find_first_not_of(' ') == string::npos) {
            cout << "Ошибка! Название не может быть пустым. Введите снова: ";
            getline(cin, name);
        }

        cout << "Введите длину трубы (км): ";
        while (!(cin >> length) || length <= 0 || cin.peek() != '\n') {
            cout << "Ошибка! Введите положительное число: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Введите диаметр трубы (мм): ";
        while (!(cin >> diameter) || diameter <= 0 || cin.peek() != '\n') {
            cout << "Ошибка! Введите положительное целое число: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Труба в ремонте? (1 - да, 0 - нет): ";
        int repairStatus;
        while (!(cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1) || cin.peek() != '\n') {
            cout << "Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        status = (repairStatus == 1);

        cin.ignore(1000, '\n');
    }

    void displayInfo(int index = -1) const {
        if (index != -1) {
            cout << "Труба #" << (index + 1) << endl;
        }
        cout << "  Название: " << name << endl;
        cout << "  Длина: " << length << " км" << endl;
        cout << "  Диаметр: " << diameter << " мм" << endl;
        cout << "  Статус: " << (status ? "В ремонте" : "Работает") << endl;
        cout << endl;
    }

    void saveToFile(ofstream& outFile, int index = -1) const {
        if (index != -1) {
            outFile << "Труба #" << (index + 1) << endl;
        }
        outFile << "  Name: " << name << endl;
        outFile << "  Length: " << length << " km" << endl;
        outFile << "  Diameter: " << diameter << " mm" << endl;
        outFile << "  Status: " << (status ? "Not worked" : "Worked") << endl;
        outFile << endl;
    }
};

class CS {
private:
    string name;
    int number_work;
    int number_work_online;
    string class_cs;

public:
    CS() : name(""), number_work(0), number_work_online(0), class_cs("") {}

    CS(string n, int num_work, int num_online, string cls)
        : name(n), number_work(num_work), number_work_online(num_online), class_cs(cls) {
    }

    string getName() const { return name; }
    int getNumberWork() const { return number_work; }
    int getNumberWorkOnline() const { return number_work_online; }
    string getClassCS() const { return class_cs; }

    void setName(const string& n) {
        if (!n.empty() || n.find_first_not_of(' ') == string::npos) {
            name = n;
        }
    }

    void setNumberWork(int num) {
        if (num > 0) {
            number_work = num;
        }
    }

    void setNumberWorkOnline(int num) {
        if (num >= 0 && num <= number_work) {
            number_work_online = num;
        }
    }

    void setClassCS(const string& cls) {
        if (!cls.empty()) {
            class_cs = cls;
        }
    }

    void startWorkshop() {
        if (number_work_online < number_work) {
            number_work_online++;
        }
    }

    void stopWorkshop() {
        if (number_work_online > 0) {
            number_work_online--;
        }
    }

    void inputFromConsole() {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Введите название КС: ";
        getline(cin, name);

        while (name.empty() || name.find_first_not_of(' ') == string::npos) {
            cout << "Ошибка! Название не может быть пустым. Введите снова: ";
            getline(cin, name);
        }

        cout << "Введите количество цехов: ";
        while (!(cin >> number_work) || number_work <= 0 || cin.peek() != '\n') {
            cout << "Ошибка! Введите положительное целое число: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Введите количество работающих цехов: ";
        while (!(cin >> number_work_online) || number_work_online < 0 ||
            number_work_online > number_work || cin.peek() != '\n') {
            if (cin.fail()) {
                cout << "Ошибка! Введите целое число: ";
            }
            else if (number_work_online > number_work) {
                cout << "Ошибка! Работающие цеха не могут превышать общее количество цехов ("
                    << number_work << "). Введите снова: ";
            }
            else {
                cout << "Ошибка! Введите неотрицательное число: ";
            }
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore(1000, '\n');

        cout << "Введите класс станций: ";
        getline(cin, class_cs);

        while (class_cs.empty()) {
            cout << "Ошибка! Класс станции не может быть пустым. Введите снова: ";
            getline(cin, class_cs);
        }
    }

    void displayInfo(int index = -1) const {
        if (index != -1) {
            cout << "КС #" << (index + 1) << endl;
        }
        cout << "  Название: " << name << endl;
        cout << "  Всего цехов: " << number_work << endl;
        cout << "  Цехов онлайн: " << number_work_online << endl;
        cout << "  Класс: " << class_cs << endl;
        cout << endl;
    }

    void saveToFile(ofstream& outFile, int index = -1) const {
        if (index != -1) {
            outFile << "КС #" << (index + 1) << endl;
        }
        outFile << "  Name: " << name << endl;
        outFile << "  all workshop: " << number_work << endl;
        outFile << "  Online workshop: " << number_work_online << endl;
        outFile << "  Class: " << class_cs << endl;
        outFile << endl;
    }
};

vector<Pipe> pipes;
vector<CS> css;
using PipelineObject = variant<Pipe, CS>;
vector<PipelineObject> container;

void Addpipe() {
    system("cls");
    cout << "=== Добавление трубы ===" << endl;

    Pipe pipe;
    pipe.inputFromConsole();
    pipes.push_back(pipe);
    container.push_back(pipe);
}

void Addcs() {
    system("cls");
    cout << "=== Добавление КС ===" << endl;

    CS cs;
    cs.inputFromConsole();
    css.push_back(cs);
    container.push_back(cs);
}

void ViewAllObjects() {
    system("cls");
    cout << "Просмотр всех объектов" << endl;

    if (pipes.empty()) {
        cout << "Трубы: не добавлены\n";
    }
    else {
        cout << "=== Трубы ===" << endl;
        for (int i = 0; i < pipes.size(); i++) {
            pipes[i].displayInfo(i);
        }
    }

    if (css.empty()) {
        cout << "КС: не добавлены" << endl;
    }
    else {
        cout << "=== Компрессорные станции ===" << endl;
        for (int i = 0; i < css.size(); i++) {
            css[i].displayInfo(i);
        }
    }

    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    while (cin.get() != '\n');
}

void EditPipe() {
    if (pipes.empty()) {
        system("cls");
        cout << "Ошибка: Трубы не добавлены!" << endl;
        cout << "Сначала добавьте трубы через меню." << endl;
        cout << "Нажмите Enter для продолжения...";
        cin.ignore(1000, '\n');
        while (cin.get() != '\n');
        return;
    }

    system("cls");
    cout << "=== Редактирование трубы ===" << endl;
    cout << "Выберите трубу для редактирования:" << endl;

    for (int i = 0; i < pipes.size(); i++) {
        cout << (i + 1) << " - " << pipes[i].getName()
            << " (длина: " << pipes[i].getLength() << " км)" << endl;
    }

    cout << "0 - Вернуться в меню" << endl;
    cout << "Выберите трубу: ";

    int pipeChoice;
    while (!(cin >> pipeChoice) || pipeChoice < 0 || pipeChoice > pipes.size() || cin.peek() != '\n') {
        cout << "Ошибка! Введите число от 0 до " << pipes.size() << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (pipeChoice == 0) {
        return;
    }

    Pipe& pipe = pipes[pipeChoice - 1];

    system("cls");
    cout << "=== Редактирование трубы ===" << endl;
    cout << "Текущие данные трубы '" << pipe.getName() << "':" << endl;
    pipe.displayInfo();

    cout << "\nЧто вы хотите изменить?" << endl;
    cout << "1 - Изменить статус ремонта" << endl;
    cout << "2 - Вернуться в меню" << endl;
    cout << "Выберите действие: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2) || cin.peek() != '\n') {
        cout << "Ошибка! Введите 1 или 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (choice == 1) {
        cout << "Текущий статус: " << (pipe.getStatus() ? "В ремонте" : "Работает") << endl;
        cout << "Изменить статус? (1 - да, 0 - нет): ";

        int change;
        while (!(cin >> change) || (change != 0 && change != 1) || cin.peek() != '\n') {
            cout << "Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (change == 1) {
            pipe.toggleStatus();
            cout << "Статус изменен. Теперь труба " << (pipe.getStatus() ? "в ремонте" : "работает") << "!" << endl;
        }
    }

    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    while (cin.get() != '\n');
}

void EditCS() {
    if (css.empty()) {
        system("cls");
        cout << "Ошибка: КС не добавлены!" << endl;
        cout << "Сначала добавьте КС через меню." << endl;
        cout << "Нажмите Enter для продолжения...";
        cin.ignore(1000, '\n');
        while (cin.get() != '\n');
        return;
    }

    system("cls");
    cout << "=== Редактирование компрессорной станции ===" << endl;
    cout << "Выберите КС для редактирования:" << endl;

    for (int i = 0; i < css.size(); i++) {
        cout << (i + 1) << " - " << css[i].getName()
            << " (цехов: " << css[i].getNumberWorkOnline() << "/" << css[i].getNumberWork() << ")" << endl;
    }

    cout << "0 - Вернуться в меню" << endl;
    cout << "Выберите КС: ";

    int csChoice;
    while (!(cin >> csChoice) || csChoice < 0 || csChoice > css.size() || cin.peek() != '\n') {
        cout << "Ошибка! Введите число от 0 до " << css.size() << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (csChoice == 0) {
        return;
    }

    CS& cs = css[csChoice - 1];

    system("cls");
    cout << "=== Редактирование компрессорной станции ===" << endl;
    cout << "Текущие данные КС '" << cs.getName() << "':" << endl;
    cs.displayInfo();

    cout << "\nЧто вы хотите изменить?" << endl;
    cout << "1 - Изменить количество работающих цехов" << endl;
    cout << "2 - Вернуться в меню" << endl;
    cout << "Выберите действие: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Ошибка! Введите 1 или 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (choice == 1) {
        cout << "Текущее состояние: " << cs.getNumberWorkOnline()
            << " из " << cs.getNumberWork() << " цехов работают" << endl;
        cout << "1 - Запустить цех" << endl;
        cout << "2 - Остановить цех" << endl;
        cout << "0 - Отмена" << endl;
        cout << "Выберите действие: ";

        int action;
        while (!(cin >> action) || action < 0 || action > 2 || cin.peek() != '\n') {
            cout << "Ошибка! Введите 0, 1 или 2: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (action) {
        case 1:
            if (cs.getNumberWorkOnline() < cs.getNumberWork()) {
                cs.startWorkshop();
                cout << "Цех запущен! Теперь работает " << cs.getNumberWorkOnline()
                    << " из " << cs.getNumberWork() << " цехов." << endl;
            }
            else {
                cout << "Ошибка: Все цехи уже работают!" << endl;
            }
            break;

        case 2:
            if (cs.getNumberWorkOnline() > 0) {
                cs.stopWorkshop();
                cout << "Цех остановлен! Теперь работает " << cs.getNumberWorkOnline()
                    << " из " << cs.getNumberWork() << " цехов." << endl;
            }
            else {
                cout << "Ошибка: Нет работающих цехов!" << endl;
            }
            break;

        case 0:
            cout << "Операция отменена." << endl;
            break;
        }
    }

    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    while (cin.get() != '\n');
}

void SaveToFile() {
    ofstream outFile("data.txt");

    if (!outFile.is_open()) {
        cout << "Ошибка: Не удалось создать или открыть файл!" << endl;
        cout << "Нажмите Enter для продолжения...";
        cin.ignore(1000, '\n');
        while (cin.get() != '\n');
        return;
    }

    outFile << "=== Pipeline system data ===" << endl;
    outFile << "======================================" << endl << endl;

    if (pipes.empty()) {
        outFile << "Трубы: не добавлены" << endl << endl;
    }
    else {
        outFile << "Трубы (всего: " << pipes.size() << "):" << endl;
        for (int i = 0; i < pipes.size(); i++) {
            pipes[i].saveToFile(outFile, i);
        }
    }

    if (css.empty()) {
        outFile << "КС: не добавлены" << endl << endl;
    }
    else {
        outFile << "Компрессорные станции (всего: " << css.size() << "):" << endl;
        for (int i = 0; i < css.size(); i++) {
            css[i].saveToFile(outFile, i);
        }
    }

    outFile.close();

    cout << "Данные сохранены в файл 'data.txt'!" << endl;
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    while (cin.get() != '\n');
}

void LoadFromFile() {
    ifstream inFile("data.txt");

    if (!inFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл 'data.txt'!" << endl;
        cout << "Нажмите Enter для продолжения...";
        cin.ignore(1000, '\n');
        while (cin.get() != '\n');
        return;
    }

    pipes.clear();
    css.clear();

    string line;
    bool readingPipe = false;
    bool readingCS = false;
    Pipe currentPipe;
    CS currentCS;
    int objectIndex = 0;

    while (getline(inFile, line)) {
        if (line.empty() || line.find("===") != string::npos ||
            line.find("======================================") != string::npos) {
            continue;
        }

        if (line.find("Труба #") != string::npos) {
            if (readingPipe && !currentPipe.getName().empty()) {
                pipes.push_back(currentPipe);
                currentPipe = Pipe();
            }
            readingPipe = true;
            readingCS = false;
            continue;
        }

        if (line.find("КС #") != string::npos) {
            if (readingCS && !currentCS.getName().empty()) {
                css.push_back(currentCS);
                currentCS = CS();
            }
            readingPipe = false;
            readingCS = true;
            continue;
        }

        if (readingPipe) {
            if (line.find("Name: ") != string::npos) {
                string name = line.substr(7);
                if (!name.empty() && name.find_first_not_of(' ') != string::npos) {
                    currentPipe.setName(name);
                }
            }
            else if (line.find("Length: ") != string::npos) {
                size_t pos = line.find(" km");
                if (pos != string::npos) {
                    string lengthStr = line.substr(10, pos - 10);
                    try {
                        float length = stof(lengthStr);
                        if (length > 0) {
                            currentPipe.setLength(length);
                        }
                    }
                    catch (const exception& e) {
                        cout << "Ошибка при чтении длины трубы: " << e.what() << endl;
                    }
                }
            }
            else if (line.find("Diameter: ") != string::npos) {
                size_t pos = line.find(" mm");
                if (pos != string::npos) {
                    string diamStr = line.substr(12, pos - 12);
                    try {
                        int diameter = stoi(diamStr);
                        if (diameter > 0) {
                            currentPipe.setDiameter(diameter);
                        }
                    }
                    catch (const exception& e) {
                        cout << "Ошибка при чтении диаметра трубы: " << e.what() << endl;
                    }
                }
            }
            else if (line.find("Status: ") != string::npos) {
                if (line.find("Not worked") != string::npos) {
                    currentPipe.setStatus(true);
                }
                else if (line.find("Worked") != string::npos) {
                    currentPipe.setStatus(false);
                }
            }
        }

        if (readingCS) {
            if (line.find("Name: ") != string::npos) {
                string name = line.substr(7);
                if (!name.empty() && name.find_first_not_of(' ') != string::npos) {
                    currentCS.setName(name);
                }
            }
            else if (line.find("all workshop: ") != string::npos) {
                string numStr = line.substr(16);
                try {
                    int num = stoi(numStr);
                    if (num > 0) {
                        currentCS.setNumberWork(num);
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка при чтении количества цехов: " << e.what() << endl;
                }
            }
            else if (line.find("Online workshop: ") != string::npos) {
                string numStr = line.substr(19);
                try {
                    int num = stoi(numStr);
                    if (num >= 0) {
                        currentCS.setNumberWorkOnline(num);
                    }
                }
                catch (const exception& e) {
                    cout << "Ошибка при чтении работающих цехов: " << e.what() << endl;
                }
            }
            else if (line.find("Class: ") != string::npos) {
                string cls = line.substr(9);
                if (!cls.empty() && cls.find_first_not_of(' ') != string::npos) {
                    currentCS.setClassCS(cls);
                }
            }
        }
    }

    if (!currentPipe.getName().empty()) {
        pipes.push_back(currentPipe);
    }
    if (!currentCS.getName().empty()) {
        css.push_back(currentCS);
    }

    inFile.close();

    cout << "Данные успешно загружены из файла 'data.txt'!" << endl;
    cout << "Загружено труб: " << pipes.size() << ", КС: " << css.size() << endl;

    for (int i = 0; i < css.size(); i++) {
        CS& cs = css[i];
        if (cs.getNumberWorkOnline() > cs.getNumberWork()) {
            cout << "Предупреждение: У КС '" << cs.getName()
                << "' количество работающих цехов (" << cs.getNumberWorkOnline()
                << ") превышает общее количество цехов (" << cs.getNumberWork()
                << "). Исправлено." << endl;
            cs.setNumberWorkOnline(cs.getNumberWork());
        }
    }

    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    while (cin.get() != '\n');
}

void ShowMenu() {
    int options;
    bool flag = true;

    while (flag) {
        system("cls");
        cout << "Меню управления трубопроводной системой:" << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить" << endl;
        cout << "7. Загрузить" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        while (!(cin >> options) || options < 0 || options > 7 || cin.peek() != '\n') {
            cout << "Ошибка! Введите число от 0 до 7: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        switch (options) {
        case 0:
            cout << "Завершение работы..." << endl;
            flag = false;
            break;
        case 1:
            Addpipe();
            cout << "Труба успешно добавлена! Всего труб: " << pipes.size() << endl;
            break;
        case 2:
            Addcs();
            cout << "КС успешно добавлена! Всего КС: " << css.size() << endl;
            break;
        case 3:
            ViewAllObjects();
            break;
        case 4:
            EditPipe();
            break;
        case 5:
            EditCS();
            break;
        case 6:
            SaveToFile();
            break;
        case 7:
            LoadFromFile();
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ShowMenu();
    return 0;
}