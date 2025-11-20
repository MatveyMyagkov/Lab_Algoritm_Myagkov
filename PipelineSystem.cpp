#include "PipelineSystem.h"
#include <windows.h>
#include <iostream>
#include <fstream>

std::map<int, Pipe> pipes;
std::map<int, CS> css;

GasNetwork gasNetwork(pipes, css);

int getNextID() {
	static int nextID = 1;

	int maxID = 0;
	for (const auto& pair : pipes) {
		if (pair.first > maxID) maxID = pair.first;
	}
	for (const auto& pair : css) {
		if (pair.first > maxID) maxID = pair.first;
	}

	nextID = max(nextID, maxID + 1);
	return nextID++;
}

std::string toLower(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

void Addpipe() {
	system("cls");
	std::cout << "=== Добавление трубы ===" << std::endl;

	Pipe pipe;
	pipe.inputFromConsole();
	int newID = getNextID();
	pipe.setID(newID);
	pipes[newID] = pipe;

	std::cout << "Труба успешно добавлена с ID: " << newID << std::endl;
}

void Addcs() {
	system("cls");
	std::cout << "=== Добавление КС ===" << std::endl;

	CS cs;
	cs.inputFromConsole();
	int newID = getNextID();
	cs.setID(newID);
	css[newID] = cs;

	std::cout << "КС успешно добавлена с ID: " << newID << std::endl;
}

void ViewAllObjects() {
	system("cls");
	std::cout << "Просмотр всех объектов" << std::endl;

	if (pipes.empty()) {
		std::cout << "Трубы: не добавлены\n";
	}
	else {
		std::cout << "=== Трубы (всего: " << pipes.size() << ") ===" << std::endl;
		int index = 0;
		for (const auto& pair : pipes) {
			pair.second.displayInfo(index++);
		}
	}

	if (css.empty()) {
		std::cout << "КС: не добавлены" << std::endl;
	}
	else {
		std::cout << "=== Компрессорные станции (всего: " << css.size() << ") ===" << std::endl;
		int index = 0;
		for (const auto& pair : css) {
			pair.second.displayInfo(index++);
		}
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void EditPipe() {
	if (pipes.empty()) {
		system("cls");
		std::cout << "Ошибка: Трубы не добавлены!" << std::endl;
		std::cout << "Сначала добавьте трубы через меню." << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	system("cls");
	std::cout << "=== Редактирование трубы ===" << std::endl;
	std::cout << "Выберите трубу для редактирования:" << std::endl;

	int index = 1;
	std::map<int, int> indexToID;

	for (const auto& pair : pipes) {
		std::cout << index << " - " << pair.second.getName()
			<< " (ID: " << pair.first << ", длина: " << pair.second.getLength() << " км)" << std::endl;
		indexToID[index] = pair.first;
		index++;
	}

	std::cout << "0 - Вернуться в меню" << std::endl;
	std::cout << "Выберите трубу: ";

	int pipeChoice;
	while (!(std::cin >> pipeChoice) || pipeChoice < 0 || pipeChoice >= index || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите число от 0 до " << (index - 1) << ": ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		logKeyboardInput(std::to_string(pipeChoice));
	}
	logKeyboardInput(std::to_string(pipeChoice));

	if (pipeChoice == 0) {
		return;
	}

	int selectedID = indexToID[pipeChoice];
	Pipe& pipe = pipes[selectedID];

	system("cls");
	std::cout << "=== Редактирование трубы ===" << std::endl;
	std::cout << "Текущие данные трубы '" << pipe.getName() << "' (ID: " << selectedID << "):" << std::endl;
	pipe.displayInfo();

	std::cout << "\nЧто вы хотите изменить?" << std::endl;
	std::cout << "1 - Изменить статус ремонта" << std::endl;
	std::cout << "2 - Вернуться в меню" << std::endl;
	std::cout << "Выберите действие: ";

	int choice;
	while (!(std::cin >> choice) || (choice != 1 && choice != 2) || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите 1 или 2: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		logKeyboardInput(std::to_string(choice));
	}
	logKeyboardInput(std::to_string(choice));

	if (choice == 1) {
		std::cout << "Текущий статус: " << (pipe.getStatus() ? "В ремонте" : "Работает") << std::endl;
		std::cout << "Изменить статус? (1 - да, 0 - нет): ";

		int change;
		while (!(std::cin >> change) || (change != 0 && change != 1) || std::cin.peek() != '\n') {
			std::cout << "Ошибка! Введите 0 или 1: ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			logKeyboardInput(std::to_string(change));
		}

		if (change == 1) {
			pipe.toggleStatus();
			std::cout << "Статус изменен. Теперь труба " << (pipe.getStatus() ? "в ремонте" : "работает") << "!" << std::endl;
		}
		logKeyboardInput(std::to_string(change));
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void EditCS() {
	if (css.empty()) {
		system("cls");
		std::cout << "Ошибка: КС не добавлены!" << std::endl;
		std::cout << "Сначала добавьте КС через меню." << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	system("cls");
	std::cout << "=== Редактирование компрессорной станции ===" << std::endl;
	std::cout << "Выберите КС для редактирования:" << std::endl;

	int index = 1;
	std::map<int, int> indexToID;

	for (const auto& pair : css) {
		std::cout << index << " - " << pair.second.getName()
			<< " (ID: " << pair.first << ", цехов: " << pair.second.getNumberWorkOnline()
			<< "/" << pair.second.getNumberWork() << ")" << std::endl;
		indexToID[index] = pair.first;
		index++;
	}

	std::cout << "0 - Вернуться в меню" << std::endl;
	std::cout << "Выберите КС: ";

	int csChoice;
	while (!(std::cin >> csChoice) || csChoice < 0 || csChoice >= index || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите число от 0 до " << (index - 1) << ": ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		logKeyboardInput(std::to_string(csChoice));
	}
	logKeyboardInput(std::to_string(csChoice));

	if (csChoice == 0) {
		return;
	}

	int selectedID = indexToID[csChoice];
	CS& cs = css[selectedID];

	system("cls");
	std::cout << "=== Редактирование компрессорной станции ===" << std::endl;
	std::cout << "Текущие данные КС '" << cs.getName() << "' (ID: " << selectedID << "):" << std::endl;
	cs.displayInfo();

	std::cout << "\nЧто вы хотите изменить?" << std::endl;
	std::cout << "1 - Изменить количество работающих цехов" << std::endl;
	std::cout << "2 - Вернуться в меню" << std::endl;
	std::cout << "Выберите действие: ";

	int choice;
	while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
		std::cout << "Ошибка! Введите 1 или 2: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		logKeyboardInput(std::to_string(choice));
	}
	logKeyboardInput(std::to_string(choice));

	if (choice == 1) {
		std::cout << "Текущее состояние: " << cs.getNumberWorkOnline()
			<< " из " << cs.getNumberWork() << " цехов работают" << std::endl;
		std::cout << "1 - Запустить цех" << std::endl;
		std::cout << "2 - Остановить цех" << std::endl;
		std::cout << "0 - Отмена" << std::endl;
		std::cout << "Выберите действие: ";

		int action;
		while (!(std::cin >> action) || action < 0 || action > 2 || std::cin.peek() != '\n') {
			std::cout << "Ошибка! Введите 0, 1 или 2: ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			logKeyboardInput(std::to_string(action));
		}
		logKeyboardInput(std::to_string(action));

		switch (action) {
		case 1:
			if (cs.getNumberWorkOnline() < cs.getNumberWork()) {
				cs.startWorkshop();
				std::cout << "Цех запущен! Теперь работает " << cs.getNumberWorkOnline()
					<< " из " << cs.getNumberWork() << " цехов." << std::endl;
			}
			else {
				std::cout << "Ошибка: Все цехи уже работают!" << std::endl;
			}
			break;

		case 2:
			if (cs.getNumberWorkOnline() > 0) {
				cs.stopWorkshop();
				std::cout << "Цех остановлен! Теперь работает " << cs.getNumberWorkOnline()
					<< " из " << cs.getNumberWork() << " цехов." << std::endl;
			}
			else {
				std::cout << "Ошибка: Нет работающих цехов!" << std::endl;
			}
			break;

		case 0:
			std::cout << "Операция отменена." << std::endl;
			break;
		}
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void RemoveAnyObjectByID() {
	system("cls");
	std::cout << "=== Удаление любого объекта по ID ===" << std::endl;

	if (pipes.empty() && css.empty()) {
		std::cout << "Ошибка: Объекты не добавлены!" << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	std::cout << "Список всех объектов:" << std::endl;

	if (!pipes.empty()) {
		std::cout << "--- Трубы ---" << std::endl;
		for (const auto& pair : pipes) {
			std::cout << "[Труба] ID: " << pair.first << " - " << pair.second.getName();
			if (gasNetwork.isPipeUsedInNetwork(pair.first)) {
				std::cout << " (Используется в сети)";
			}
			std::cout << std::endl;
		}
	}

	if (!css.empty()) {
		std::cout << "--- КС ---" << std::endl;
		for (const auto& pair : css) {
			std::cout << "[КС] ID: " << pair.first << " - " << pair.second.getName() << std::endl;
		}
	}

	std::cout << "\nВведите ID объекта для удаления: ";
	int idToDelete;
	while (!(std::cin >> idToDelete) || idToDelete <= 0 || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите положительное целое число: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	logKeyboardInput(std::to_string(idToDelete));

	bool found = false;
	std::string objectType = "";
	std::string objectName = "";

	auto pipeIt = pipes.find(idToDelete);
	if (pipeIt != pipes.end()) {
		if (gasNetwork.isPipeUsedInNetwork(idToDelete)) {
			std::cout << "Ошибка: Труба '" << pipeIt->second.getName()
				<< "' используется в газотранспортной сети и не может быть удалена!" << std::endl;
			std::cout << "Сначала отключите трубу от сети через соответствующее меню." << std::endl;

			std::cout << "Нажмите Enter для продолжения...";
			std::cin.ignore(1000, '\n');
			while (std::cin.get() != '\n');
			return;
		}

		objectType = "Труба";
		objectName = pipeIt->second.getName();
		pipes.erase(pipeIt);
		found = true;
	}

	if (!found) {
		auto csIt = css.find(idToDelete);
		if (csIt != css.end()) {
			objectType = "КС";
			objectName = csIt->second.getName();
			css.erase(csIt);
			found = true;
		}
	}

	if (found) {
		std::cout << objectType << " '" << objectName << "' с ID " << idToDelete << " успешно удалена!" << std::endl;
		std::cout << "Осталось труб: " << pipes.size() << ", КС: " << css.size() << std::endl;
	}
	else {
		std::cout << "Объект с ID " << idToDelete << " не найден!" << std::endl;
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void SaveToCustomFile() {
	system("cls");
	std::cout << "=== Сохранение в файл ===" << std::endl;

	std::string filename;
	std::cout << "Введите название файла для сохранения (например: data.txt): ";
	std::cin.ignore(1000, '\n');
	std::getline(std::cin, filename);

	while (filename.empty() || filename.find_first_not_of(' ') == std::string::npos) {
		std::cout << "Ошибка! Имя файла не может быть пустым. Введите снова: ";
		std::getline(std::cin, filename);
		logKeyboardInput(filename);
	}
	logKeyboardInput(filename);

	std::ofstream outFile(filename);

	if (!outFile.is_open()) {
		std::cout << "Ошибка: Не удалось создать или открыть файл '" << filename << "'!" << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	outFile << "=== Pipeline system data ===" << std::endl;
	outFile << "======================================" << std::endl << std::endl;

	if (pipes.empty()) {
		outFile << "Трубы: не добавлены" << std::endl << std::endl;
	}
	else {
		outFile << "Трубы (всего: " << pipes.size() << "):" << std::endl;
		int index = 0;
		for (const auto& pair : pipes) {
			pair.second.saveToFile(outFile, index++);
		}
	}

	if (css.empty()) {
		outFile << "КС: не добавлены" << std::endl << std::endl;
	}
	else {
		outFile << "Компрессорные станции (всего: " << css.size() << "):" << std::endl;
		int index = 0;
		for (const auto& pair : css) {
			pair.second.saveToFile(outFile, index++);
		}
	}

	outFile.close();

	std::cout << "Данные успешно сохранены в файл '" << filename << "'!" << std::endl;
	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void LoadFromCustomFile() {
	system("cls");
	std::cout << "=== Загрузка из файла ===" << std::endl;

	std::string filename;
	std::cout << "Введите название файла для загрузки (например: data.txt): ";
	std::cin.ignore(1000, '\n');
	std::getline(std::cin, filename);
	logKeyboardInput(filename);

	while (filename.empty() || filename.find_first_not_of(' ') == std::string::npos) {
		std::cout << "Ошибка! Имя файла не может быть пустым. Введите снова: ";
		std::getline(std::cin, filename);
	}

	std::ifstream inFile(filename);

	if (!inFile.is_open()) {
		std::cout << "Ошибка: Не удалось открыть файл '" << filename << "'!" << std::endl;
		std::cout << "Проверьте правильность имени файла и его существование." << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	pipes.clear();
	css.clear();

	std::string line;
	bool readingPipe = false;
	bool readingCS = false;
	Pipe currentPipe;
	CS currentCS;

	auto extractValue = [](const std::string& line, const std::string& marker) -> std::string {
		size_t pos = line.find(marker);
		if (pos != std::string::npos) {
			std::string value = line.substr(pos + marker.length());
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);
			return value;
		}
		return "";
		};

	while (getline(inFile, line)) {
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		if (line.empty() || line.find("===") != std::string::npos ||
			line.find("======================================") != std::string::npos) {
			continue;
		}

		if (line.find("Труба #") != std::string::npos) {
			if (readingPipe && !currentPipe.getName().empty()) {
				pipes[currentPipe.getID()] = currentPipe;
				currentPipe = Pipe();
			}
			readingPipe = true;
			readingCS = false;
			continue;
		}

		if (line.find("КС #") != std::string::npos) {
			if (readingCS && !currentCS.getName().empty()) {
				css[currentCS.getID()] = currentCS;
				currentCS = CS();
			}
			readingPipe = false;
			readingCS = true;
			continue;
		}

		if (readingPipe) {
			if (line.find("ID:") != std::string::npos) {
				std::string value = extractValue(line, "ID:");
				if (!value.empty()) {
					try {
						currentPipe.setID(std::stoi(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения ID трубы: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Name:") != std::string::npos) {
				std::string value = extractValue(line, "Name:");
				if (!value.empty()) {
					currentPipe.setName(value);
				}
			}
			else if (line.find("Length:") != std::string::npos) {
				std::string value = extractValue(line, "Length:");
				size_t kmPos = value.find(" km");
				if (kmPos != std::string::npos) {
					value = value.substr(0, kmPos);
				}
				if (!value.empty()) {
					try {
						currentPipe.setLength(std::stof(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения длины трубы: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Diameter:") != std::string::npos) {
				std::string value = extractValue(line, "Diameter:");
				size_t mmPos = value.find(" mm");
				if (mmPos != std::string::npos) {
					value = value.substr(0, mmPos);
				}
				if (!value.empty()) {
					try {
						currentPipe.setDiameter(std::stoi(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения диаметра трубы: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Status:") != std::string::npos) {
				std::string value = extractValue(line, "Status:");
				if (value.find("Not worked") != std::string::npos) {
					currentPipe.setStatus(true);
				}
				else if (value.find("Worked") != std::string::npos) {
					currentPipe.setStatus(false);
				}
			}
		}

		if (readingCS) {
			if (line.find("ID:") != std::string::npos) {
				std::string value = extractValue(line, "ID:");
				if (!value.empty()) {
					try {
						currentCS.setID(std::stoi(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения ID КС: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Name:") != std::string::npos) {
				std::string value = extractValue(line, "Name:");
				if (!value.empty()) {
					currentCS.setName(value);
				}
			}
			else if (line.find("all workshop:") != std::string::npos) {
				std::string value = extractValue(line, "all workshop:");
				if (!value.empty()) {
					try {
						currentCS.setNumberWork(std::stoi(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения количества цехов: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Online workshop:") != std::string::npos) {
				std::string value = extractValue(line, "Online workshop:");
				if (!value.empty()) {
					try {
						currentCS.setNumberWorkOnline(std::stoi(value));
					}
					catch (const std::exception& e) {
						std::cout << "Ошибка чтения работающих цехов: " << e.what() << std::endl;
					}
				}
			}
			else if (line.find("Class:") != std::string::npos) {
				std::string value = extractValue(line, "Class:");
				if (!value.empty()) {
					currentCS.setClassCS(value);
				}
			}
		}
	}

	if (!currentPipe.getName().empty()) {
		pipes[currentPipe.getID()] = currentPipe;
	}
	if (!currentCS.getName().empty()) {
		css[currentCS.getID()] = currentCS;
	}

	inFile.close();

	std::cout << "Данные успешно загружены из файла '" << filename << "'!" << std::endl;
	std::cout << "Загружено труб: " << pipes.size() << ", КС: " << css.size() << std::endl;

	for (auto& pair : css) {
		CS& cs = pair.second;
		if (cs.getNumberWorkOnline() > cs.getNumberWork()) {
			std::cout << "Предупреждение: У КС '" << cs.getName()
				<< "' исправлено количество работающих цехов." << std::endl;
			cs.setNumberWorkOnline(cs.getNumberWork());
		}
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void SearchCS() {
	system("cls");
	std::cout << "=== Поиск КС по фильтрам ===" << std::endl;

	if (css.empty()) {
		std::cout << "Ошибка: КС не добавлены!" << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	std::string searchName;
	double minUnusedPercent = -1.0;

	std::cout << "Введите название КС для поиска (или оставьте пустым для пропуска): ";
	std::cin.ignore(1000, '\n');
	std::getline(std::cin, searchName);
	logKeyboardInput(searchName);

	std::cout << "Фильтр по проценту незадействованных цехов:" << std::endl;
	std::cout << "Введите минимальный процент незадействованных цехов (0-100) или -1 для пропуска: ";

	while (!(std::cin >> minUnusedPercent) || (minUnusedPercent != -1 && (minUnusedPercent < 0 || minUnusedPercent > 100)) || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите число от 0 до 100 или -1 для пропуска: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	logKeyboardInput(std::to_string(minUnusedPercent));

	std::vector<CS> results;

	for (const auto& pair : css) {
		const CS& cs = pair.second;
		bool nameMatch = true;
		bool percentMatch = true;

		if (!searchName.empty()) {
			std::string csNameLower = toLower(cs.getName());
			std::string searchNameLower = toLower(searchName);
			if (csNameLower.find(searchNameLower) == std::string::npos) {
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
		std::cout << "КС по заданным критериям не найдены." << std::endl;
	}
	else {
		std::cout << "=== Результаты поиска ===" << std::endl;
		std::cout << "Найдено КС: " << results.size() << std::endl;
		for (size_t i = 0; i < results.size(); i++) {
			const auto& cs = results[i];
			cs.displayInfo(i);
			if (cs.getNumberWork() > 0) {
				double unusedPercent = (1.0 - (double)cs.getNumberWorkOnline() / cs.getNumberWork()) * 100.0;
				std::cout << " Процент незадействованных цехов: " << std::fixed << std::setprecision(1) << unusedPercent << "%" << std::endl;
			}
			else {
				std::cout << " Процент незадействованных цехов: 100% (нет цехов)" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void ChangePipeStatusByID(int id, bool newStatus) {
	auto it = pipes.find(id);
	if (it != pipes.end()) {
		it->second.setStatus(newStatus);
	}
}

void BatchChangePipeStatus(const std::vector<int>& pipeIDs, bool newStatus) {
	for (int id : pipeIDs) {
		ChangePipeStatusByID(id, newStatus);
	}
}

void BatchDeletePipes(const std::vector<int>& pipeIDs) {
	for (int id : pipeIDs) {
		auto it = pipes.find(id);
		if (it != pipes.end()) {
			std::cout << "Удалена труба: " << it->second.getName() << " (ID: " << it->first << ")" << std::endl;
			pipes.erase(it);
		}
	}
}

void SearchPipesWithBatchOperations() {
	system("cls");
	std::cout << "=== Поиск труб по фильтрам с пакетными операциями ===" << std::endl;

	if (pipes.empty()) {
		std::cout << "Ошибка: Трубы не добавлены!" << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	std::string searchName;
	int repairStatus = -1;

	std::cout << "Введите название трубы для поиска (или оставьте пустым для пропуска): ";
	std::cin.ignore(1000, '\n');
	std::getline(std::cin, searchName);
	logKeyboardInput(searchName);

	std::cout << "Фильтр по статусу ремонта:" << std::endl;
	std::cout << "0 - Только работающие трубы" << std::endl;
	std::cout << "1 - Только трубы в ремонте" << std::endl;
	std::cout << "2 - Любой статус (пропустить фильтр)" << std::endl;
	std::cout << "Выберите фильтр: ";

	while (!(std::cin >> repairStatus) || repairStatus < 0 || repairStatus > 2 || std::cin.peek() != '\n') {
		std::cout << "Ошибка! Введите число от 0 до 2: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		logKeyboardInput(std::to_string(repairStatus));
	}
	logKeyboardInput(std::to_string(repairStatus));

	std::vector<Pipe> results;
	std::vector<int> foundIDs;

	for (const auto& pair : pipes) {
		const Pipe& pipe = pair.second;
		bool nameMatch = true;
		bool statusMatch = true;

		if (!searchName.empty()) {
			std::string pipeNameLower = toLower(pipe.getName());
			std::string searchNameLower = toLower(searchName);
			if (pipeNameLower.find(searchNameLower) == std::string::npos) {
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
			foundIDs.push_back(pair.first);
		}
	}

	if (results.empty()) {
		std::cout << "Трубы по заданным критериям не найдены." << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	std::cout << "=== Результаты поиска ===" << std::endl;
	std::cout << "Найдено труб: " << results.size() << std::endl;
	for (int i = 0; i < results.size(); i++) {
		results[i].displayInfo(i);
	}

	int batchChoice;
	do {
		std::cout << "\n=== Пакетные операции ===" << std::endl;
		std::cout << "1. Изменить статус ремонта для всех найденных труб" << std::endl;
		std::cout << "2. Удалить все найденные трубы" << std::endl;
		std::cout << "3. Выбрать конкретные трубы для изменения статуса" << std::endl;
		std::cout << "4. Выбрать конкретные трубы для удаления" << std::endl;
		std::cout << "0. Вернуться в главное меню" << std::endl;
		std::cout << "Выберите операцию: ";

		while (!(std::cin >> batchChoice) || batchChoice < 0 || batchChoice > 4 || std::cin.peek() != '\n') {
			std::cout << "Ошибка! Введите число от 0 до 4: ";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			logKeyboardInput(std::to_string(batchChoice));
		}
		logKeyboardInput(std::to_string(batchChoice));

		switch (batchChoice) {
		case 1: {
			std::cout << "Установить статус для всех найденных труб:" << std::endl;
			std::cout << "0 - Работает" << std::endl;
			std::cout << "1 - В ремонте" << std::endl;
			std::cout << "Выберите статус: ";

			int newStatus;
			while (!(std::cin >> newStatus) || (newStatus != 0 && newStatus != 1) || std::cin.peek() != '\n') {
				std::cout << "Ошибка! Введите 0 или 1: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				logKeyboardInput(std::to_string(newStatus));
			}
			logKeyboardInput(std::to_string(newStatus));

			BatchChangePipeStatus(foundIDs, newStatus == 1);
			std::cout << "Статус изменен для " << foundIDs.size() << " труб." << std::endl;
			break;
		}

		case 2: {
			std::cout << "Вы уверены, что хотите удалить все " << foundIDs.size() << " найденных труб?" << std::endl;
			std::cout << "1 - Да, удалить все" << std::endl;
			std::cout << "0 - Нет, отменить" << std::endl;
			std::cout << "Выберите действие: ";

			int confirm;
			while (!(std::cin >> confirm) || (confirm != 0 && confirm != 1) || std::cin.peek() != '\n') {
				std::cout << "Ошибка! Введите 0 или 1: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				logKeyboardInput(std::to_string(confirm));
			}
			logKeyboardInput(std::to_string(confirm));

			if (confirm == 1) {
				BatchDeletePipes(foundIDs);
				std::cout << "Удалено " << foundIDs.size() << " труб." << std::endl;
				foundIDs.clear();
			}
			else {
				std::cout << "Удаление отменено." << std::endl;
			}
			break;
		}

		case 3: {
			if (foundIDs.empty()) {
				std::cout << "Нет доступных труб для выбора." << std::endl;
				break;
			}

			std::cout << "Введите ID труб для изменения статуса (через пробел): ";
			std::cin.ignore(1000, '\n');
			std::string input;
			std::getline(std::cin, input);

			std::vector<int> selectedIDs;
			std::stringstream ss(input);
			int id;
			while (ss >> id) {
				if (std::find(foundIDs.begin(), foundIDs.end(), id) != foundIDs.end()) {
					selectedIDs.push_back(id);
				}
				else {
					std::cout << "ID " << id << " не найден в результатах поиска." << std::endl;
				}
			}

			if (!selectedIDs.empty()) {
				std::cout << "Установить статус для выбранных труб:" << std::endl;
				std::cout << "0 - Работает" << std::endl;
				std::cout << "1 - В ремонте" << std::endl;
				std::cout << "Выберите статус: ";

				int newStatus;
				while (!(std::cin >> newStatus) || (newStatus != 0 && newStatus != 1) || std::cin.peek() != '\n') {
					std::cout << "Ошибка! Введите 0 или 1: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					logKeyboardInput(std::to_string(newStatus));
				}
				logKeyboardInput(std::to_string(newStatus));

				BatchChangePipeStatus(selectedIDs, newStatus == 1);
				std::cout << "Статус изменен для " << selectedIDs.size() << " труб." << std::endl;
			}
			break;
		}

		case 4: {
			if (foundIDs.empty()) {
				std::cout << "Нет доступных труб для выбора." << std::endl;
				break;
			}

			std::cout << "Введите ID труб для удаления (через пробел): ";
			std::cin.ignore(1000, '\n');
			std::string input;
			std::getline(std::cin, input);

			std::vector<int> selectedIDs;
			std::stringstream ss(input);
			int id;
			while (ss >> id) {
				if (std::find(foundIDs.begin(), foundIDs.end(), id) != foundIDs.end()) {
					selectedIDs.push_back(id);
				}
				else {
					std::cout << "ID " << id << " не найден в результатах поиска." << std::endl;
				}
			}

			if (!selectedIDs.empty()) {
				std::cout << "Вы уверены, что хотите удалить " << selectedIDs.size() << " труб?" << std::endl;
				std::cout << "1 - Да, удалить" << std::endl;
				std::cout << "0 - Нет, отменить" << std::endl;
				std::cout << "Выберите действие: ";

				int confirm;
				while (!(std::cin >> confirm) || (confirm != 0 && confirm != 1) || std::cin.peek() != '\n') {
					std::cout << "Ошибка! Введите 0 или 1: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					logKeyboardInput(std::to_string(confirm));
				}
				logKeyboardInput(std::to_string(confirm));

				if (confirm == 1) {
					BatchDeletePipes(selectedIDs);
					std::cout << "Удалено " << selectedIDs.size() << " труб." << std::endl;

					for (int id : selectedIDs) {
						auto it = std::find(foundIDs.begin(), foundIDs.end(), id);
						if (it != foundIDs.end()) {
							foundIDs.erase(it);
						}
					}
				}
				else {
					std::cout << "Удаление отменено." << std::endl;
				}
			}
			break;
		}

		case 0:
			std::cout << "Возврат в главное меню..." << std::endl;
			break;
		}

		if (batchChoice == 2 || batchChoice == 4) {
			results.clear();
			for (int id : foundIDs) {
				auto it = pipes.find(id);
				if (it != pipes.end()) {
					results.push_back(it->second);
				}
			}

			if (results.empty()) {
				std::cout << "Больше нет труб, соответствующих критериям поиска." << std::endl;
				break;
			}
			else {
				std::cout << "\nОбновленные результаты поиска (" << results.size() << " труб):" << std::endl;
				for (int i = 0; i < results.size(); i++) {
					results[i].displayInfo(i);
				}
			}
		}

	} while (batchChoice != 0);

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void ConnectCSWithPipe() {
	system("cls");
	std::cout << "=== Соединение КС трубой ===" << std::endl;

	if (css.size() < 2) {
		std::cout << "Ошибка: Для соединения необходимо как минимум 2 КС!" << std::endl;
		std::cout << "Нажмите Enter для продолжения...";
		std::cin.ignore(1000, '\n');
		while (std::cin.get() != '\n');
		return;
	}

	std::cout << "Доступные КС:" << std::endl;
	for (const auto& csPair : css) {
		std::cout << "ID: " << csPair.first << " - " << csPair.second.getName() << std::endl;
	}

	int sourceCS, destinationCS, diameter;

	std::cout << "Введите ID КС входа: ";
	while (!(std::cin >> sourceCS) || css.find(sourceCS) == css.end()) {
		std::cout << "Ошибка! Введите существующий ID КС: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	std::cout << "Введите ID КС выхода: ";
	while (!(std::cin >> destinationCS) || css.find(destinationCS) == css.end() || destinationCS == sourceCS) {
		if (destinationCS == sourceCS) {
			std::cout << "Ошибка! КС входа и выхода не могут совпадать. Введите другой ID: ";
		}
		else {
			std::cout << "Ошибка! Введите существующий ID КС: ";
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	std::cout << "Доступные диаметры: 500, 700, 1000, 1400 мм" << std::endl;
	std::cout << "Введите диаметр трубы: ";
	while (!(std::cin >> diameter)) {
		std::cout << "Ошибка! Введите целое число: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	if (!gasNetwork.connectCS(sourceCS, destinationCS, diameter)) {
		std::cout << "Не удалось создать соединение." << std::endl;
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void DisplayGasNetwork() {
	system("cls");
	gasNetwork.displayNetwork();
	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void DisconnectPipeFromNetwork() {
	system("cls");
	std::cout << "=== Отключение трубы от сети ===" << std::endl;

	std::cout << "Введите ID трубы для отключения: ";
	int pipeID;
	while (!(std::cin >> pipeID) || pipeID <= 0) {
		std::cout << "Ошибка! Введите положительное целое число: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	if (!gasNetwork.disconnectPipe(pipeID)) {
		std::cout << "Труба с ID " << pipeID << " не найдена в сети или не существует." << std::endl;
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}

void TopologicalSort() {
	system("cls");
	std::cout << "=== Топологическая сортировка газотранспортной сети ===" << std::endl;

	std::vector<int> sorted = gasNetwork.topologicalSort();

	if (sorted.empty()) {
		std::cout << "Сеть пуста или содержит циклы." << std::endl;
	}
	else {
		std::cout << "Топологический порядок КС:" << std::endl;
		for (size_t i = 0; i < sorted.size(); ++i) {
			auto it = css.find(sorted[i]);
			if (it != css.end()) {
				std::cout << i + 1 << ". КС " << sorted[i] << " - " << it->second.getName() << std::endl;
			}
			else {
				std::cout << i + 1 << ". КС " << sorted[i] << " (не найдена в базе)" << std::endl;
			}
		}
	}

	std::cout << "Нажмите Enter для продолжения...";
	std::cin.ignore(1000, '\n');
	while (std::cin.get() != '\n');
}