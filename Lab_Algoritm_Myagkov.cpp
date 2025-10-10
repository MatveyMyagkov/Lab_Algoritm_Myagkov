#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <variant>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

class KeyboardLogger {
private:
	std::ofstream logFile;

public:
	KeyboardLogger(const std::string& filename = "keyboard_actions.log") {
		logFile.open(filename);
		if (!logFile.is_open()) {
			std::cerr << "Cannot open log file!" << std::endl;
		}
	}

	~KeyboardLogger() {
		if (logFile.is_open()) {
			logFile.close();
		}
	}

	void log(const std::string& input) {
		if (logFile.is_open() && !input.empty()) {
			logFile << input << std::endl;
			logFile.flush();
		}
	}
};

KeyboardLogger keyLogger;

void logKeyboardInput(const string& input) {
	keyLogger.log(input);
}

class Pipe {
private:
	int id;
	string name;
	float length;
	int diameter;
	bool status;


public:
	Pipe() : id(0), name(""), length(0.0f), diameter(0), status(false) {}

	Pipe(int(i), string n, float len, int diam, bool stat)
		:id(i), name(n), length(len), diameter(diam), status(stat) {
	}
	int getID() const { return id; }
	string getName() const { return name; }
	float getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool getStatus() const { return status; }

	void display() const { cout << "Труба: " << name << " (ID: " << id << ")" << endl; }

	void setID(const int& i) {
		id = i;
	}

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
		string name_input;
		getline(cin, name_input);
		logKeyboardInput(name_input);
		setName(name_input);

		while (name.empty() || name.find_first_not_of(' ') == string::npos) {
			cout << "Ошибка! Название не может быть пустым. Введите снова: ";
			getline(cin, name);
			getline(cin, name);
			logKeyboardInput(name);
		}
		
		cout << "Введите длину трубы (км): ";
		float length;
		while (!(cin >> length) || length <= 0 || cin.peek() != '\n') {
			cout << "Ошибка! Введите положительное число: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(length));
		}
		logKeyboardInput(to_string(length));

		cout << "Введите диаметр трубы (мм): ";
		int diameter;
		while (!(cin >> diameter) || diameter <= 0 || cin.peek() != '\n') {
			cout << "Ошибка! Введите положительное целое число: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(diameter));
		}
		logKeyboardInput(to_string(diameter));

		cout << "Труба в ремонте? (1 - да, 0 - нет): ";
		int repairStatus;
		while (!(cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1) || cin.peek() != '\n') {
			cout << "Ошибка! Введите 0 или 1: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(repairStatus));
		}
		status = (repairStatus == 1);
		logKeyboardInput(to_string(repairStatus));
		cin.ignore(1000, '\n');
	}

	void displayInfo(int index = -1) const {
		if (index != -1) {
			cout << "Труба #" << (index + 1) << endl;
		}
		cout << "  (ID: " << id << ")" << endl;
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
		outFile << "  ID: " << id << endl;
		outFile << "  Name: " << name << endl;
		outFile << "  Length: " << length << " km" << endl;
		outFile << "  Diameter: " << diameter << " mm" << endl;
		outFile << "  Status: " << (status ? "Not worked" : "Worked") << endl;
		outFile << endl;
	}
};

class CS {
private:
	int id;
	string name;
	int number_work;
	int number_work_online;
	string class_cs;

public:
	CS() : id(0), name(""), number_work(0), number_work_online(0), class_cs("") {}

	CS(int i, string n, int num_work, int num_online, string cls)
		: id(i), name(n), number_work(num_work), number_work_online(num_online), class_cs(cls) {
	}
	int getID() const { return id; }
	string getName() const { return name; }
	int getNumberWork() const { return number_work; }
	int getNumberWorkOnline() const { return number_work_online; }
	string getClassCS() const { return class_cs; }

	void display() const { cout << "КС: " << name << " (ID: " << id << ")" << endl; }

	void setID(const int& i) {
		id = i;
	}
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
		string name_input;
		getline(cin, name_input);
		setName(name_input);

		while (name.empty() || name.find_first_not_of(' ') == string::npos) {
			cout << "Ошибка! Название не может быть пустым. Введите снова: ";
			getline(cin, name);
			logKeyboardInput(name_input);
		}
		logKeyboardInput(name_input);

		cout << "Введите количество цехов: ";
		int number_work;
		while (!(cin >> number_work) || number_work <= 0 || cin.peek() != '\n') {
			cout << "Ошибка! Введите положительное целое число: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(number_work));
		}
		logKeyboardInput(to_string(number_work));

		cout << "Введите количество работающих цехов: ";
		int number_work_online;
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
			logKeyboardInput(to_string(number_work_online));
		}
		
		cin.ignore(1000, '\n');
		logKeyboardInput(to_string(number_work_online));
		cout << "Введите класс станций: ";
		getline(cin, class_cs);

		while (class_cs.empty()) {
			cout << "Ошибка! Класс станции не может быть пустым. Введите снова: ";
			getline(cin, class_cs);
			logKeyboardInput(class_cs);
		}
		logKeyboardInput(class_cs);
	}

	void displayInfo(int index = -1) const {
		if (index != -1) {
			cout << "КС #" << (index + 1) << endl;
		}
		cout << "  (ID: " << id << ")" << endl;
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
		outFile << "  ID: " << id << endl;
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
	pipe.setID(container.size() + 1);
	pipes.push_back(pipe);
	container.push_back(pipe);
}

void Addcs() {
	system("cls");
	cout << "=== Добавление КС ===" << endl;

	CS cs;
	cs.inputFromConsole();
	cs.setID(container.size() + 1);
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
	if (container.empty()) {
		cout << "Контейнер: не добавлены" << endl;
	}
	else {
		cout << "=== Перебор контейнера ===" << endl;

		for (const auto& obj : container) {
			visit([](const auto& item) {
				item.display();
				}, obj);
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
		logKeyboardInput(to_string(pipeChoice));
	}
	logKeyboardInput(to_string(pipeChoice));

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
		logKeyboardInput(to_string(choice));
	}
	logKeyboardInput(to_string(choice));

	if (choice == 1) {
		cout << "Текущий статус: " << (pipe.getStatus() ? "В ремонте" : "Работает") << endl;
		cout << "Изменить статус? (1 - да, 0 - нет): ";

		int change;
		while (!(cin >> change) || (change != 0 && change != 1) || cin.peek() != '\n') {
			cout << "Ошибка! Введите 0 или 1: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(change));
		}
		

		if (change == 1) {
			pipe.toggleStatus();
			cout << "Статус изменен. Теперь труба " << (pipe.getStatus() ? "в ремонте" : "работает") << "!" << endl;
		}
		logKeyboardInput(to_string(change));
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
		logKeyboardInput(to_string(csChoice));
	}
	logKeyboardInput(to_string(csChoice));

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
		logKeyboardInput(to_string(choice));
	}
	logKeyboardInput(to_string(choice));

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
			logKeyboardInput(to_string(action));
		}
		logKeyboardInput(to_string(action));
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

void SaveToCustomFile() {
	system("cls");
	cout << "=== Сохранение в файл ===" << endl;

	string filename;
	cout << "Введите название файла для сохранения (например: data.txt): ";
	cin.ignore(1000, '\n');
	getline(cin, filename);


	while (filename.empty() || filename.find_first_not_of(' ') == string::npos) {
		cout << "Ошибка! Имя файла не может быть пустым. Введите снова: ";
		getline(cin, filename);
		logKeyboardInput(filename);
	}
	logKeyboardInput(filename);

	ofstream outFile(filename);

	if (!outFile.is_open()) {
		cout << "Ошибка: Не удалось создать или открыть файл '" << filename << "'!" << endl;
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

	cout << "Данные успешно сохранены в файл '" << filename << "'!" << endl;
	cout << "Нажмите Enter для продолжения...";
	cin.ignore(1000, '\n');
	while (cin.get() != '\n');
}

void LoadFromCustomFile() {
	system("cls");
	cout << "=== Загрузка из файла ===" << endl;

	string filename;
	cout << "Введите название файла для загрузки (например: data.txt): ";
	cin.ignore(1000, '\n');
	getline(cin, filename);
	logKeyboardInput(filename);

	while (filename.empty() || filename.find_first_not_of(' ') == string::npos) {
		cout << "Ошибка! Имя файла не может быть пустым. Введите снова: ";
		getline(cin, filename);
	}

	ifstream inFile(filename);

	if (!inFile.is_open()) {
		cout << "Ошибка: Не удалось открыть файл '" << filename << "'!" << endl;
		cout << "Проверьте правильность имени файла и его существование." << endl;
		cout << "Нажмите Enter для продолжения...";
		cin.ignore(1000, '\n');
		while (cin.get() != '\n');
		return;
	}

	pipes.clear();
	css.clear();
	container.clear();

	string line;
	bool readingPipe = false;
	bool readingCS = false;
	Pipe currentPipe;
	CS currentCS;

	auto extractValue = [](const string& line, const string& marker) -> string {
		size_t pos = line.find(marker);
		if (pos != string::npos) {
			string value = line.substr(pos + marker.length());
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);
			return value;
		}
		return "";
		};

	while (getline(inFile, line)) {
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		if (line.empty() || line.find("===") != string::npos ||
			line.find("======================================") != string::npos) {
			continue;
		}

		if (line.find("Труба #") != string::npos) {
			if (readingPipe && !currentPipe.getName().empty()) {
				pipes.push_back(currentPipe);
				container.push_back(currentPipe);
				currentPipe = Pipe();
			}
			readingPipe = true;
			readingCS = false;
			continue;
		}

		if (line.find("КС #") != string::npos) {
			if (readingCS && !currentCS.getName().empty()) {
				css.push_back(currentCS);
				container.push_back(currentCS);
				currentCS = CS();
			}
			readingPipe = false;
			readingCS = true;
			continue;
		}

		if (readingPipe) {
			if (line.find("ID:") != string::npos) {
				string value = extractValue(line, "ID:");
				if (!value.empty()) {
					try {
						currentPipe.setID(stoi(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения ID трубы: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Name:") != string::npos) {
				string value = extractValue(line, "Name:");
				if (!value.empty()) {
					currentPipe.setName(value);
				}
			}
			else if (line.find("Length:") != string::npos) {
				string value = extractValue(line, "Length:");
				size_t kmPos = value.find(" km");
				if (kmPos != string::npos) {
					value = value.substr(0, kmPos);
				}
				if (!value.empty()) {
					try {
						currentPipe.setLength(stof(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения длины трубы: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Diameter:") != string::npos) {
				string value = extractValue(line, "Diameter:");
				size_t mmPos = value.find(" mm");
				if (mmPos != string::npos) {
					value = value.substr(0, mmPos);
				}
				if (!value.empty()) {
					try {
						currentPipe.setDiameter(stoi(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения диаметра трубы: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Status:") != string::npos) {
				string value = extractValue(line, "Status:");
				if (value.find("Not worked") != string::npos) {
					currentPipe.setStatus(true);
				}
				else if (value.find("Worked") != string::npos) {
					currentPipe.setStatus(false);
				}
			}
		}

		if (readingCS) {
			if (line.find("ID:") != string::npos) {
				string value = extractValue(line, "ID:");
				if (!value.empty()) {
					try {
						currentCS.setID(stoi(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения ID КС: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Name:") != string::npos) {
				string value = extractValue(line, "Name:");
				if (!value.empty()) {
					currentCS.setName(value);
				}
			}
			else if (line.find("all workshop:") != string::npos) {
				string value = extractValue(line, "all workshop:");
				if (!value.empty()) {
					try {
						currentCS.setNumberWork(stoi(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения количества цехов: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Online workshop:") != string::npos) {
				string value = extractValue(line, "Online workshop:");
				if (!value.empty()) {
					try {
						currentCS.setNumberWorkOnline(stoi(value));
					}
					catch (const exception& e) {
						cout << "Ошибка чтения работающих цехов: " << e.what() << endl;
					}
				}
			}
			else if (line.find("Class:") != string::npos) {
				string value = extractValue(line, "Class:");
				if (!value.empty()) {
					currentCS.setClassCS(value);
				}
			}
		}
	}

	if (!currentPipe.getName().empty()) {
		pipes.push_back(currentPipe);
		container.push_back(currentPipe);
	}
	if (!currentCS.getName().empty()) {
		css.push_back(currentCS);
		container.push_back(currentCS);
	}

	inFile.close();

	cout << "Данные успешно загружены из файла '" << filename << "'!" << endl;
	cout << "Загружено труб: " << pipes.size() << ", КС: " << css.size()
		<< ", Всего в контейнере: " << container.size() << endl;

	for (int i = 0; i < css.size(); i++) {
		CS& cs = css[i];
		if (cs.getNumberWorkOnline() > cs.getNumberWork()) {
			cout << "Предупреждение: У КС '" << cs.getName()
				<< "' исправлено количество работающих цехов." << endl;
			cs.setNumberWorkOnline(cs.getNumberWork());
		}
	}

	cout << "Нажмите Enter для продолжения...";
	cin.ignore(1000, '\n');
	while (cin.get() != '\n');
}


void RemoveAnyObjectByID() {
	system("cls");
	cout << "=== Удаление любого объекта по ID ===" << endl;

	if (container.empty()) {
		cout << "Ошибка: Объекты не добавлены!" << endl;
		cout << "Нажмите Enter для продолжения...";
		cin.ignore(1000, '\n');
		while (cin.get() != '\n');
		return;
	}

	cout << "Список всех объектов:" << endl;
	for (const auto& obj : container) {
		visit([](const auto& item) {
			using T = decay_t<decltype(item)>;
			if constexpr (is_same_v<T, Pipe>) {
				cout << "[Труба] ID: " << item.getID() << " - " << item.getName() << endl;
			}
			else if constexpr (is_same_v<T, CS>) {
				cout << "[КС] ID: " << item.getID() << " - " << item.getName() << endl;
			}
			}, obj);
	}

	cout << "\nВведите ID объекта для удаления: ";
	int idToDelete;
	while (!(cin >> idToDelete) || idToDelete <= 0 || cin.peek() != '\n') {
		cout << "Ошибка! Введите положительное целое число: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	logKeyboardInput(to_string(idToDelete));
	bool found = false;
	string objectType = "";
	string objectName = "";

	for (auto it = container.begin(); it != container.end(); ) {
		bool shouldDelete = false;

		visit([idToDelete, &shouldDelete, &objectType, &objectName](auto& item) {
			if (item.getID() == idToDelete) {
				shouldDelete = true;
				using T = decay_t<decltype(item)>;
				if constexpr (is_same_v<T, Pipe>) {
					objectType = "Труба";
				}
				else if constexpr (is_same_v<T, CS>) {
					objectType = "КС";
				}
				objectName = item.getName();
			}
			}, *it);

		if (shouldDelete) {
			it = container.erase(it);
			found = true;
			break;
		}
		else {
			++it;
		}
	}

	if (found) {
		for (auto it = pipes.begin(); it != pipes.end(); ) {
			if (it->getID() == idToDelete) {
				it = pipes.erase(it);
				break;
			}
			else {
				++it;
			}
		}

		for (auto it = css.begin(); it != css.end(); ) {
			if (it->getID() == idToDelete) {
				it = css.erase(it);
				break;
			}
			else {
				++it;
			}
		}

		cout << objectType << " '" << objectName << "' с ID " << idToDelete << " успешно удалена!" << endl;
		cout << "Осталось труб: " << pipes.size() << ", КС: " << css.size()
			<< ", объектов в контейнере: " << container.size() << endl;
	}
	else {
		cout << "Объект с ID " << idToDelete << " не найден!" << endl;
	}

	cout << "Нажмите Enter для продолжения...";
	cin.ignore(1000, '\n');
	while (cin.get() != '\n');
}

string toLower(const string& str) {
	string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

void SearchCS() {
	system("cls");
	cout << "=== Поиск КС по фильтрам ===" << endl;

	if (css.empty()) {
		cout << "Ошибка: КС не добавлены!" << endl;
		cout << "Нажмите Enter для продолжения...";
		cin.ignore(1000, '\n');
		while (cin.get() != '\n');
		return;
	}

	string searchName;
	double minUnusedPercent = -1.0;

	cout << "Введите название КС для поиска (или оставьте пустым для пропуска): ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	logKeyboardInput(searchName);

	cout << "Фильтр по проценту незадействованных цехов:" << endl;
	cout << "Введите минимальный процент незадействованных цехов (0-100) или -1 для пропуска: ";

	while (!(cin >> minUnusedPercent) || (minUnusedPercent != -1 && (minUnusedPercent < 0 || minUnusedPercent > 100)) || cin.peek() != '\n') {
		cout << "Ошибка! Введите число от 0 до 100 или -1 для пропуска: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	logKeyboardInput(to_string(minUnusedPercent));

	vector<CS> results;

	for (const auto& cs : css) {
		bool nameMatch = true;
		bool percentMatch = true;

		if (!searchName.empty()) {
			string csNameLower = toLower(cs.getName());
			string searchNameLower = toLower(searchName);
			if (csNameLower.find(searchNameLower) == string::npos) {
				nameMatch = false;
			}
		}

		if (minUnusedPercent != -1) {
			if (cs.getNumberWork() > 0) {
				double unusedPercent = (1.0 - (double)cs.getNumberWorkOnline() / cs.getNumberWork()) * 100.0;
				if (unusedPercent < minUnusedPercent) {
					percentMatch = false;
				}
			}
			else {
				percentMatch = (minUnusedPercent <= 100.0);
			}
		}

		if (nameMatch && percentMatch) {
			results.push_back(cs);
		}
	}

	if (results.empty()) {
		cout << "КС по заданным критериям не найдены." << endl;
	}
	else {
		cout << "=== Результаты поиска ===" << endl;
		cout << "Найдено КС: " << results.size() << endl;
		for (size_t i = 0; i < results.size(); i++) {
			const auto& cs = results[i];
			cs.displayInfo(i);
			if (cs.getNumberWork() > 0) {
				double unusedPercent = (1.0 - (double)cs.getNumberWorkOnline() / cs.getNumberWork()) * 100.0;
				cout << " Процент незадействованных цехов: " << fixed << setprecision(1) << unusedPercent << "%" << endl;
			}
			else {
				cout << " Процент незадействованных цехов: 100% (нет цехов)" << endl;
			}
			cout << endl;
		}

	}

	cout << "Нажмите Enter для продолжения...";
	cin.ignore(1000, '\n');
	while (cin.get() != '\n');
}

// Функция для изменения статуса трубы по ID
void ChangePipeStatusByID(int id, bool newStatus) {
	for (auto& pipe : pipes) {
		if (pipe.getID() == id) {
			pipe.setStatus(newStatus);
			break;
		}
	}

	for (auto& obj : container) {
		if (holds_alternative<Pipe>(obj)) {
			Pipe& pipe = get<Pipe>(obj);
			if (pipe.getID() == id) {
				pipe.setStatus(newStatus);
				break;
			}
		}
	}
}

// Функция для пакетного изменения статуса труб
void BatchChangePipeStatus(const vector<int>& pipeIDs, bool newStatus) {
	for (int id : pipeIDs) {
		ChangePipeStatusByID(id, newStatus);
	}
}

// Функция для пакетного удаления труб
void BatchDeletePipes(const vector<int>& pipeIDs) {
	for (auto it = pipes.begin(); it != pipes.end(); ) {
		if (find(pipeIDs.begin(), pipeIDs.end(), it->getID()) != pipeIDs.end()) {
			cout << "Удалена труба: " << it->getName() << " (ID: " << it->getID() << ")" << endl;
			it = pipes.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = container.begin(); it != container.end(); ) {
		if (holds_alternative<Pipe>(*it)) {
			Pipe pipe = get<Pipe>(*it);
			if (find(pipeIDs.begin(), pipeIDs.end(), pipe.getID()) != pipeIDs.end()) {
				it = container.erase(it);
			}
			else {
				++it;
			}
		}
		else {
			++it;
		}
	}
}

void SearchPipesWithBatchOperations() {
	system("cls");
	cout << "=== Поиск труб по фильтрам с пакетными операциями ===" << endl;

	if (pipes.empty()) {
		cout << "Ошибка: Трубы не добавлены!" << endl;
		cout << "Нажмите Enter для продолжения...";
		cin.ignore(1000, '\n');
		while (cin.get() != '\n');
		return;
	}

	string searchName;
	int repairStatus = -1;

	cout << "Введите название трубы для поиска (или оставьте пустым для пропуска): ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	logKeyboardInput(searchName);

	cout << "Фильтр по статусу ремонта:" << endl;
	cout << "0 - Только работающие трубы" << endl;
	cout << "1 - Только трубы в ремонте" << endl;
	cout << "2 - Любой статус (пропустить фильтр)" << endl;
	cout << "Выберите фильтр: ";

	while (!(cin >> repairStatus) || repairStatus < 0 || repairStatus > 2 || cin.peek() != '\n') {
		cout << "Ошибка! Введите число от 0 до 2: ";
		cin.clear();
		cin.ignore(1000, '\n');
		logKeyboardInput(to_string(repairStatus));
	}
	logKeyboardInput(to_string(repairStatus));

	vector<Pipe> results;
	vector<int> foundIDs;

	for (const auto& pipe : pipes) {
		bool nameMatch = true;
		bool statusMatch = true;

		if (!searchName.empty()) {
			string pipeNameLower = toLower(pipe.getName());
			string searchNameLower = toLower(searchName);
			if (pipeNameLower.find(searchNameLower) == string::npos) {
				nameMatch = false;
			}
		}

		if (repairStatus != 2) {
			bool requiredStatus = (repairStatus == 1);
			if (pipe.getStatus() != requiredStatus) {
				statusMatch = false;
			}
		}

		if (nameMatch && statusMatch) {
			results.push_back(pipe);
			foundIDs.push_back(pipe.getID());
		}
	}

	if (results.empty()) {
		cout << "Трубы по заданным критериям не найдены." << endl;
		cout << "Нажмите Enter для продолжения...";
		cin.ignore(1000, '\n');
		while (cin.get() != '\n');
		return;
	}

	cout << "=== Результаты поиска ===" << endl;
	cout << "Найдено труб: " << results.size() << endl;
	for (int i = 0; i < results.size(); i++) {
		results[i].displayInfo(i);
	}

	int batchChoice;
	do {
		cout << "\n=== Пакетные операции ===" << endl;
		cout << "1. Изменить статус ремонта для всех найденных труб" << endl;
		cout << "2. Удалить все найденные трубы" << endl;
		cout << "3. Выбрать конкретные трубы для изменения статуса" << endl;
		cout << "4. Выбрать конкретные трубы для удаления" << endl;
		cout << "0. Вернуться в главное меню" << endl;
		cout << "Выберите операцию: ";

		while (!(cin >> batchChoice) || batchChoice < 0 || batchChoice > 4 || cin.peek() != '\n') {
			cout << "Ошибка! Введите число от 0 до 4: ";
			cin.clear();
			cin.ignore(1000, '\n');
			logKeyboardInput(to_string(batchChoice));
		}
		logKeyboardInput(to_string(batchChoice));

		switch (batchChoice) {
		case 1: {
			cout << "Установить статус для всех найденных труб:" << endl;
			cout << "0 - Работает" << endl;
			cout << "1 - В ремонте" << endl;
			cout << "Выберите статус: ";

			int newStatus;
			while (!(cin >> newStatus) || (newStatus != 0 && newStatus != 1) || cin.peek() != '\n') {
				cout << "Ошибка! Введите 0 или 1: ";
				cin.clear();
				cin.ignore(1000, '\n');
				logKeyboardInput(to_string(newStatus));
			}
			logKeyboardInput(to_string(newStatus));

			BatchChangePipeStatus(foundIDs, newStatus == 1);
			cout << "Статус изменен для " << foundIDs.size() << " труб." << endl;
			break;
		}

		case 2: {
			cout << "Вы уверены, что хотите удалить все " << foundIDs.size() << " найденных труб?" << endl;
			cout << "1 - Да, удалить все" << endl;
			cout << "0 - Нет, отменить" << endl;
			cout << "Выберите действие: ";

			int confirm;
			while (!(cin >> confirm) || (confirm != 0 && confirm != 1) || cin.peek() != '\n') {
				cout << "Ошибка! Введите 0 или 1: ";
				cin.clear();
				cin.ignore(1000, '\n');
				logKeyboardInput(to_string(confirm));
			}
			logKeyboardInput(to_string(confirm));

			if (confirm == 1) {
				BatchDeletePipes(foundIDs);
				cout << "Удалено " << foundIDs.size() << " труб." << endl;
				foundIDs.clear();
			}
			else {
				cout << "Удаление отменено." << endl;
			}
			break;
		}

		case 3: {
			if (foundIDs.empty()) {
				cout << "Нет доступных труб для выбора." << endl;
				break;
			}

			cout << "Введите ID труб для изменения статуса (через пробел): ";
			cin.ignore(1000, '\n');
			string input;
			getline(cin, input);

			vector<int> selectedIDs;
			stringstream ss(input);
			int id;
			while (ss >> id) {
				if (find(foundIDs.begin(), foundIDs.end(), id) != foundIDs.end()) {
					selectedIDs.push_back(id);
				}
				else {
					cout << "ID " << id << " не найден в результатах поиска." << endl;
				}
			}

			if (!selectedIDs.empty()) {
				cout << "Установить статус для выбранных труб:" << endl;
				cout << "0 - Работает" << endl;
				cout << "1 - В ремонте" << endl;
				cout << "Выберите статус: ";

				int newStatus;
				while (!(cin >> newStatus) || (newStatus != 0 && newStatus != 1) || cin.peek() != '\n') {
					cout << "Ошибка! Введите 0 или 1: ";
					cin.clear();
					cin.ignore(1000, '\n');
					logKeyboardInput(to_string(newStatus));
				}
				logKeyboardInput(to_string(newStatus));

				BatchChangePipeStatus(selectedIDs, newStatus == 1);
				cout << "Статус изменен для " << selectedIDs.size() << " труб." << endl;
			}
			break;
		}

		case 4: {
			if (foundIDs.empty()) {
				cout << "Нет доступных труб для выбора." << endl;
				break;
			}

			cout << "Введите ID труб для удаления (через пробел): ";
			cin.ignore(1000, '\n');
			string input;
			getline(cin, input);

			vector<int> selectedIDs;
			stringstream ss(input);
			int id;
			while (ss >> id) {
				if (find(foundIDs.begin(), foundIDs.end(), id) != foundIDs.end()) {
					selectedIDs.push_back(id);
				}
				else {
					cout << "ID " << id << " не найден в результатах поиска." << endl;
				}
			}

			if (!selectedIDs.empty()) {
				cout << "Вы уверены, что хотите удалить " << selectedIDs.size() << " труб?" << endl;
				cout << "1 - Да, удалить" << endl;
				cout << "0 - Нет, отменить" << endl;
				cout << "Выберите действие: ";

				int confirm;
				while (!(cin >> confirm) || (confirm != 0 && confirm != 1) || cin.peek() != '\n') {
					cout << "Ошибка! Введите 0 или 1: ";
					cin.clear();
					cin.ignore(1000, '\n');
					logKeyboardInput(to_string(confirm));
				}
				logKeyboardInput(to_string(confirm));

				if (confirm == 1) {
					BatchDeletePipes(selectedIDs);
					cout << "Удалено " << selectedIDs.size() << " труб." << endl;

					for (int id : selectedIDs) {
						auto it = find(foundIDs.begin(), foundIDs.end(), id);
						if (it != foundIDs.end()) {
							foundIDs.erase(it);
						}
					}
				}
				else {
					cout << "Удаление отменено." << endl;
				}
			}
			break;
		}

		case 0:
			cout << "Возврат в главное меню..." << endl;
			break;
		}

		if (batchChoice == 2 || batchChoice == 4) {
			results.clear();
			for (const auto& pipe : pipes) {
				if (find(foundIDs.begin(), foundIDs.end(), pipe.getID()) != foundIDs.end()) {
					results.push_back(pipe);
				}
			}

			if (results.empty()) {
				cout << "Больше нет труб, соответствующих критериям поиска." << endl;
				break;
			}
			else {
				cout << "\nОбновленные результаты поиска (" << results.size() << " труб):" << endl;
				for (int i = 0; i < results.size(); i++) {
					results[i].displayInfo(i);
				}
			}
		}

	} while (batchChoice != 0);

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
		cout << "8. Удалить объект по ID" << endl;
		cout << "9. Поиск труб по названию, по признаку «в ремонте (С возможностью пакетного редактирования)" << endl;
		cout << "10. Поиск КС по названию, по проценту незадействованных цехов" << endl;
		cout << "0. Выход" << endl;
		cout << "Выберите действие: ";

		while (!(cin >> options) || options < 0 || options > 10 || cin.peek() != '\n') {
			cout << "Ошибка! Введите число от 0 до 10: ";
			cin.clear();
			while (cin.get() != '\n');
			logKeyboardInput(to_string(options));
		}
		logKeyboardInput(to_string(options));
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
			SaveToCustomFile();
			break;
		case 7:
			LoadFromCustomFile();
			break;
		case 8:
			RemoveAnyObjectByID();
		case 9:
			SearchPipesWithBatchOperations();
			break;
		case 10:
			SearchCS();
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