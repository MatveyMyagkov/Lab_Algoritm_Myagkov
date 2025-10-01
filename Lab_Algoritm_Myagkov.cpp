#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Pipe {
    string Name;
    float length;
    int diametr;
    bool status;
};

struct CS {
    string Name;
    int number_work;
    int number_work_online;
    string class_cs;
};

vector<Pipe> pipes;
vector<CS> css;

void Addpipe() {
    system("cls");
    cout << "=== Добавление трубы ===" << endl;

    Pipe pipe;

    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Введите километровую отметку (Название трубы): ";
    getline(cin, pipe.Name);

    while (pipe.Name.empty()) {
        cout << "Ошибка! Название не может быть пустым. Введите снова: ";
        getline(cin, pipe.Name);
    }

    cout << "Введите длину трубы (км): ";
    while (!(cin >> pipe.length) || pipe.length <= 0 || cin.peek() != '\n') {
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Введите диаметр трубы (мм): ";
    while (!(cin >> pipe.diametr) || pipe.diametr <= 0 || cin.peek() != '\n') {
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
    pipe.status = (repairStatus == 1);

    pipes.push_back(pipe);
    cin.ignore(1000, '\n');
}

void Addcs() {
    system("cls");
    cout << "=== Добавление КС ===" << endl;

    CS cs;

    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Введите название КС: ";
    getline(cin, cs.Name);

    while (cs.Name.empty()) {
        cout << "Ошибка! Название не может быть пустым. Введите снова: ";
        getline(cin, cs.Name);
    }

    cout << "Введите количество цехов: ";
    while (!(cin >> cs.number_work) || cs.number_work <= 0 || cin.peek() != '\n') {
        cout << "Ошибка! Введите положительное целое число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Введите количество работающих цехов: ";
    while (!(cin >> cs.number_work_online) || cs.number_work_online < 0 ||
        cs.number_work_online > cs.number_work || cin.peek() != '\n') {
        if (cin.fail()) {
            cout << "Ошибка! Введите целое число: ";
        }
        else if (cs.number_work_online > cs.number_work) {
            cout << "Ошибка! Работающие цеха не могут превышать общее количество цехов ("
                << cs.number_work << "). Введите снова: ";
        }
        else {
            cout << "Ошибка! Введите неотрицательное число: ";
        }
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore(1000, '\n');

    cout << "Введите класс станций (некий показатель, обобщающий различные специфические характеристики): ";
    getline(cin, cs.class_cs);

    while (cs.class_cs.empty()) {
        cout << "Ошибка! Класс станции не может быть пустым. Введите снова: ";
        getline(cin, cs.class_cs);
    }

    css.push_back(cs);
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
            cout << "Труба #" << (i + 1) << endl;
            cout << "  Название: " << pipes[i].Name << endl;
            cout << "  Длина: " << pipes[i].length << " км" << endl;
            cout << "  Диаметр: " << pipes[i].diametr << " мм" << endl;
            cout << "  Статус: " << (pipes[i].status ? "В ремонте" : "Работает") << endl;
            cout << endl;
        }
    }
    if (css.empty()) {
        cout << "КС: не добавлены" << endl;
    }
    else {
        cout << "=== Компрессорные станции ===" << endl;
        for (int i = 0; i < css.size(); i++) {
            cout << "КС #" << (i + 1) << endl;
            cout << "  Название: " << css[i].Name << endl;
            cout << "  Всего цехов: " << css[i].number_work << endl;
            cout << "  Цехов онлайн: " << css[i].number_work_online << endl;
            cout << "  Класс: " << css[i].class_cs << endl;
            cout << endl;
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
        cout << (i + 1) << " - " << pipes[i].Name << " (длина: " << pipes[i].length << " км)" << endl;
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
    cout << "Текущие данные трубы '" << pipe.Name << "':" << endl;
    cout << "1. Название: " << pipe.Name << endl;
    cout << "2. Длина: " << pipe.length << " км" << endl;
    cout << "3. Диаметр: " << pipe.diametr << " мм" << endl;
    cout << "4. Статус: " << (pipe.status ? "В ремонте" : "Работает") << endl;

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
        cout << "Текущий статус: " << (pipe.status ? "В ремонте" : "Работает") << endl;
        cout << "Изменить статус? (1 - да, 0 - нет): ";

        int change;
        while (!(cin >> change) || (change != 0 && change != 1) || cin.peek() != '\n') {
            cout << "Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (change == 1) {
            pipe.status = !pipe.status;
            cout << "Статус изменен. Теперь труба " << (pipe.status ? "в ремонте" : "работает") << "!" << endl;
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
        cout << (i + 1) << " - " << css[i].Name << " (цехов: " << css[i].number_work_online << "/" << css[i].number_work << ")" << endl;
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
    cout << "Текущие данные КС '" << cs.Name << "':" << endl;
    cout << "1. Название: " << cs.Name << endl;
    cout << "2. Всего цехов: " << cs.number_work << endl;
    cout << "3. Работающих цехов: " << cs.number_work_online << endl;
    cout << "4. Класс: " << cs.class_cs << endl;

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
        cout << "Текущее состояние: " << cs.number_work_online
            << " из " << cs.number_work << " цехов работают" << endl;
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
            if (cs.number_work_online < cs.number_work) {
                cs.number_work_online++;
                cout << "Цех запущен! Теперь работает " << cs.number_work_online
                    << " из " << cs.number_work << " цехов." << endl;
            }
            else {
                cout << "Ошибка: Все цехи уже работают!" << endl;
            }
            break;

        case 2:
            if (cs.number_work_online > 0) {
                cs.number_work_online--;
                cout << "Цех остановлен! Теперь работает " << cs.number_work_online
                    << " из " << cs.number_work << " цехов." << endl;
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
            outFile << "Труба #" << (i + 1) << endl;
            outFile << "  Name: " << pipes[i].Name << endl;
            outFile << "  Length: " << pipes[i].length << " km" << endl;
            outFile << "  Diameter: " << pipes[i].diametr << " mm" << endl;
            outFile << "  Status: " << (pipes[i].status ? "Not worked" : "Worked") << endl;
            outFile << endl;
        }
    }
    if (css.empty()) {
        outFile << "КС: не добавлены" << endl << endl;
    }
    else {
        outFile << "Компрессорные станции (всего: " << css.size() << "):" << endl;
        for (int i = 0; i < css.size(); i++) {
            outFile << "КС #" << (i + 1) << endl;
            outFile << "  Name: " << css[i].Name << endl;
            outFile << "  all workshop: " << css[i].number_work << endl;
            outFile << "  Online workshop: " << css[i].number_work_online << endl;
            outFile << "  Class: " << css[i].class_cs << endl;
            outFile << endl;
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

    while (getline(inFile, line)) {
        if (line.find("Труба #") != string::npos) {
            if (currentPipe.Name != "") {
                pipes.push_back(currentPipe);
            }
            currentPipe = Pipe();
            readingPipe = true;
            readingCS = false;
            continue;
        }
        else if (line.find("КС #") != string::npos) {
            if (currentCS.Name != "") {
                css.push_back(currentCS);
            }
            currentCS = CS();
            readingPipe = false;
            readingCS = true;
            continue;
        }
        else if (line.find("Name: ") != string::npos) {
            if (readingPipe) {
                currentPipe.Name = line.substr(7);
            }
            else if (readingCS) {
                currentCS.Name = line.substr(7);
            }
        }
        else if (line.find("Length: ") != string::npos) {
            size_t pos = line.find(" km");
            if (pos != string::npos) {
                string lengthStr = line.substr(10, pos - 10);
                currentPipe.length = stof(lengthStr);
            }
        }
        else if (line.find("Diameter: ") != string::npos) {
            size_t pos = line.find(" mm");
            if (pos != string::npos) {
                string diamStr = line.substr(12, pos - 12);
                currentPipe.diametr = stoi(diamStr);
            }
        }
        else if (line.find("Status: ") != string::npos) {
            if (line.find("Not worked") != string::npos) {
                currentPipe.status = true;
            }
            else if (line.find("Worked") != string::npos) {
                currentPipe.status = false;
            }
        }
        else if (line.find("all workshop: ") != string::npos) {
            currentCS.number_work = stoi(line.substr(16));
        }
        else if (line.find("Online workshop: ") != string::npos) {
            currentCS.number_work_online = stoi(line.substr(19));
        }
        else if (line.find("Class: ") != string::npos) {
            currentCS.class_cs = line.substr(9);
        }
    }

    if (currentPipe.Name != "") {
        pipes.push_back(currentPipe);
    }
    if (currentCS.Name != "") {
        css.push_back(currentCS);
    }

    inFile.close();

    cout << "Данные успешно загружены из файла 'data.txt'!" << endl;
    cout << "Загружено труб: " << pipes.size() << ", КС: " << css.size() << endl;
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