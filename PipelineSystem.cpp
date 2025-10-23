#include "PipelineSystem.h"
#include <windows.h>
#include <iostream>
#include <fstream>

std::map<int, Pipe> pipes;
std::map<int, CS> css;

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
    std::cout << "=== ���������� ����� ===" << std::endl;

    Pipe pipe;
    pipe.inputFromConsole();
    int newID = getNextID();
    pipe.setID(newID);
    pipes[newID] = pipe;

    std::cout << "����� ������� ��������� � ID: " << newID << std::endl;
}

void Addcs() {
    system("cls");
    std::cout << "=== ���������� �� ===" << std::endl;

    CS cs;
    cs.inputFromConsole();
    int newID = getNextID();
    cs.setID(newID);
    css[newID] = cs;

    std::cout << "�� ������� ��������� � ID: " << newID << std::endl;
}

void ViewAllObjects() {
    system("cls");
    std::cout << "�������� ���� ��������" << std::endl;

    if (pipes.empty()) {
        std::cout << "�����: �� ���������\n";
    }
    else {
        std::cout << "=== ����� (�����: " << pipes.size() << ") ===" << std::endl;
        int index = 0;
        for (const auto& pair : pipes) {
            pair.second.displayInfo(index++);
        }
    }

    if (css.empty()) {
        std::cout << "��: �� ���������" << std::endl;
    }
    else {
        std::cout << "=== ������������� ������� (�����: " << css.size() << ") ===" << std::endl;
        int index = 0;
        for (const auto& pair : css) {
            pair.second.displayInfo(index++);
        }
    }

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void EditPipe() {
    if (pipes.empty()) {
        system("cls");
        std::cout << "������: ����� �� ���������!" << std::endl;
        std::cout << "������� �������� ����� ����� ����." << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    system("cls");
    std::cout << "=== �������������� ����� ===" << std::endl;
    std::cout << "�������� ����� ��� ��������������:" << std::endl;

    int index = 1;
    std::map<int, int> indexToID;

    for (const auto& pair : pipes) {
        std::cout << index << " - " << pair.second.getName()
            << " (ID: " << pair.first << ", �����: " << pair.second.getLength() << " ��)" << std::endl;
        indexToID[index] = pair.first;
        index++;
    }

    std::cout << "0 - ��������� � ����" << std::endl;
    std::cout << "�������� �����: ";

    int pipeChoice;
    while (!(std::cin >> pipeChoice) || pipeChoice < 0 || pipeChoice >= index || std::cin.peek() != '\n') {
        std::cout << "������! ������� ����� �� 0 �� " << (index - 1) << ": ";
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
    std::cout << "=== �������������� ����� ===" << std::endl;
    std::cout << "������� ������ ����� '" << pipe.getName() << "' (ID: " << selectedID << "):" << std::endl;
    pipe.displayInfo();

    std::cout << "\n��� �� ������ ��������?" << std::endl;
    std::cout << "1 - �������� ������ �������" << std::endl;
    std::cout << "2 - ��������� � ����" << std::endl;
    std::cout << "�������� ��������: ";

    int choice;
    while (!(std::cin >> choice) || (choice != 1 && choice != 2) || std::cin.peek() != '\n') {
        std::cout << "������! ������� 1 ��� 2: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(choice));
    }
    logKeyboardInput(std::to_string(choice));

    if (choice == 1) {
        std::cout << "������� ������: " << (pipe.getStatus() ? "� �������" : "��������") << std::endl;
        std::cout << "�������� ������? (1 - ��, 0 - ���): ";

        int change;
        while (!(std::cin >> change) || (change != 0 && change != 1) || std::cin.peek() != '\n') {
            std::cout << "������! ������� 0 ��� 1: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            logKeyboardInput(std::to_string(change));
        }

        if (change == 1) {
            pipe.toggleStatus();
            std::cout << "������ �������. ������ ����� " << (pipe.getStatus() ? "� �������" : "��������") << "!" << std::endl;
        }
        logKeyboardInput(std::to_string(change));
    }

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void EditCS() {
    if (css.empty()) {
        system("cls");
        std::cout << "������: �� �� ���������!" << std::endl;
        std::cout << "������� �������� �� ����� ����." << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    system("cls");
    std::cout << "=== �������������� ������������� ������� ===" << std::endl;
    std::cout << "�������� �� ��� ��������������:" << std::endl;

    int index = 1;
    std::map<int, int> indexToID;

    for (const auto& pair : css) {
        std::cout << index << " - " << pair.second.getName()
            << " (ID: " << pair.first << ", �����: " << pair.second.getNumberWorkOnline()
            << "/" << pair.second.getNumberWork() << ")" << std::endl;
        indexToID[index] = pair.first;
        index++;
    }

    std::cout << "0 - ��������� � ����" << std::endl;
    std::cout << "�������� ��: ";

    int csChoice;
    while (!(std::cin >> csChoice) || csChoice < 0 || csChoice >= index || std::cin.peek() != '\n') {
        std::cout << "������! ������� ����� �� 0 �� " << (index - 1) << ": ";
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
    std::cout << "=== �������������� ������������� ������� ===" << std::endl;
    std::cout << "������� ������ �� '" << cs.getName() << "' (ID: " << selectedID << "):" << std::endl;
    cs.displayInfo();

    std::cout << "\n��� �� ������ ��������?" << std::endl;
    std::cout << "1 - �������� ���������� ���������� �����" << std::endl;
    std::cout << "2 - ��������� � ����" << std::endl;
    std::cout << "�������� ��������: ";

    int choice;
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "������! ������� 1 ��� 2: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        logKeyboardInput(std::to_string(choice));
    }
    logKeyboardInput(std::to_string(choice));

    if (choice == 1) {
        std::cout << "������� ���������: " << cs.getNumberWorkOnline()
            << " �� " << cs.getNumberWork() << " ����� ��������" << std::endl;
        std::cout << "1 - ��������� ���" << std::endl;
        std::cout << "2 - ���������� ���" << std::endl;
        std::cout << "0 - ������" << std::endl;
        std::cout << "�������� ��������: ";

        int action;
        while (!(std::cin >> action) || action < 0 || action > 2 || std::cin.peek() != '\n') {
            std::cout << "������! ������� 0, 1 ��� 2: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            logKeyboardInput(std::to_string(action));
        }
        logKeyboardInput(std::to_string(action));

        switch (action) {
        case 1:
            if (cs.getNumberWorkOnline() < cs.getNumberWork()) {
                cs.startWorkshop();
                std::cout << "��� �������! ������ �������� " << cs.getNumberWorkOnline()
                    << " �� " << cs.getNumberWork() << " �����." << std::endl;
            }
            else {
                std::cout << "������: ��� ���� ��� ��������!" << std::endl;
            }
            break;

        case 2:
            if (cs.getNumberWorkOnline() > 0) {
                cs.stopWorkshop();
                std::cout << "��� ����������! ������ �������� " << cs.getNumberWorkOnline()
                    << " �� " << cs.getNumberWork() << " �����." << std::endl;
            }
            else {
                std::cout << "������: ��� ���������� �����!" << std::endl;
            }
            break;

        case 0:
            std::cout << "�������� ��������." << std::endl;
            break;
        }
    }

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void RemoveAnyObjectByID() {
    system("cls");
    std::cout << "=== �������� ������ ������� �� ID ===" << std::endl;

    if (pipes.empty() && css.empty()) {
        std::cout << "������: ������� �� ���������!" << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    std::cout << "������ ���� ��������:" << std::endl;

    if (!pipes.empty()) {
        std::cout << "--- ����� ---" << std::endl;
        for (const auto& pair : pipes) {
            std::cout << "[�����] ID: " << pair.first << " - " << pair.second.getName() << std::endl;
        }
    }

    if (!css.empty()) {
        std::cout << "--- �� ---" << std::endl;
        for (const auto& pair : css) {
            std::cout << "[��] ID: " << pair.first << " - " << pair.second.getName() << std::endl;
        }
    }

    std::cout << "\n������� ID ������� ��� ��������: ";
    int idToDelete;
    while (!(std::cin >> idToDelete) || idToDelete <= 0 || std::cin.peek() != '\n') {
        std::cout << "������! ������� ������������� ����� �����: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    logKeyboardInput(std::to_string(idToDelete));

    bool found = false;
    std::string objectType = "";
    std::string objectName = "";

    auto pipeIt = pipes.find(idToDelete);
    if (pipeIt != pipes.end()) {
        objectType = "�����";
        objectName = pipeIt->second.getName();
        pipes.erase(pipeIt);
        found = true;
    }

    if (!found) {
        auto csIt = css.find(idToDelete);
        if (csIt != css.end()) {
            objectType = "��";
            objectName = csIt->second.getName();
            css.erase(csIt);
            found = true;
        }
    }

    if (found) {
        std::cout << objectType << " '" << objectName << "' � ID " << idToDelete << " ������� �������!" << std::endl;
        std::cout << "�������� ����: " << pipes.size() << ", ��: " << css.size() << std::endl;
    }
    else {
        std::cout << "������ � ID " << idToDelete << " �� ������!" << std::endl;
    }

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void SaveToCustomFile() {
    system("cls");
    std::cout << "=== ���������� � ���� ===" << std::endl;

    std::string filename;
    std::cout << "������� �������� ����� ��� ���������� (��������: data.txt): ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, filename);

    while (filename.empty() || filename.find_first_not_of(' ') == std::string::npos) {
        std::cout << "������! ��� ����� �� ����� ���� ������. ������� �����: ";
        std::getline(std::cin, filename);
        logKeyboardInput(filename);
    }
    logKeyboardInput(filename);

    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "������: �� ������� ������� ��� ������� ���� '" << filename << "'!" << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    outFile << "=== Pipeline system data ===" << std::endl;
    outFile << "======================================" << std::endl << std::endl;

    if (pipes.empty()) {
        outFile << "�����: �� ���������" << std::endl << std::endl;
    }
    else {
        outFile << "����� (�����: " << pipes.size() << "):" << std::endl;
        int index = 0;
        for (const auto& pair : pipes) {
            pair.second.saveToFile(outFile, index++);
        }
    }

    if (css.empty()) {
        outFile << "��: �� ���������" << std::endl << std::endl;
    }
    else {
        outFile << "������������� ������� (�����: " << css.size() << "):" << std::endl;
        int index = 0;
        for (const auto& pair : css) {
            pair.second.saveToFile(outFile, index++);
        }
    }

    outFile.close();

    std::cout << "������ ������� ��������� � ���� '" << filename << "'!" << std::endl;
    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void LoadFromCustomFile() {
    system("cls");
    std::cout << "=== �������� �� ����� ===" << std::endl;

    std::string filename;
    std::cout << "������� �������� ����� ��� �������� (��������: data.txt): ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, filename);
    logKeyboardInput(filename);

    while (filename.empty() || filename.find_first_not_of(' ') == std::string::npos) {
        std::cout << "������! ��� ����� �� ����� ���� ������. ������� �����: ";
        std::getline(std::cin, filename);
    }

    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cout << "������: �� ������� ������� ���� '" << filename << "'!" << std::endl;
        std::cout << "��������� ������������ ����� ����� � ��� �������������." << std::endl;
        std::cout << "������� Enter ��� �����������...";
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

        if (line.find("����� #") != std::string::npos) {
            if (readingPipe && !currentPipe.getName().empty()) {
                pipes[currentPipe.getID()] = currentPipe;
                currentPipe = Pipe();
            }
            readingPipe = true;
            readingCS = false;
            continue;
        }

        if (line.find("�� #") != std::string::npos) {
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
                        std::cout << "������ ������ ID �����: " << e.what() << std::endl;
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
                        std::cout << "������ ������ ����� �����: " << e.what() << std::endl;
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
                        std::cout << "������ ������ �������� �����: " << e.what() << std::endl;
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
                        std::cout << "������ ������ ID ��: " << e.what() << std::endl;
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
                        std::cout << "������ ������ ���������� �����: " << e.what() << std::endl;
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
                        std::cout << "������ ������ ���������� �����: " << e.what() << std::endl;
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

    std::cout << "������ ������� ��������� �� ����� '" << filename << "'!" << std::endl;
    std::cout << "��������� ����: " << pipes.size() << ", ��: " << css.size() << std::endl;

    for (auto& pair : css) {
        CS& cs = pair.second;
        if (cs.getNumberWorkOnline() > cs.getNumberWork()) {
            std::cout << "��������������: � �� '" << cs.getName()
                << "' ���������� ���������� ���������� �����." << std::endl;
            cs.setNumberWorkOnline(cs.getNumberWork());
        }
    }

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}

void SearchCS() {
    system("cls");
    std::cout << "=== ����� �� �� �������� ===" << std::endl;

    if (css.empty()) {
        std::cout << "������: �� �� ���������!" << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    std::string searchName;
    double minUnusedPercent = -1.0;

    std::cout << "������� �������� �� ��� ������ (��� �������� ������ ��� ��������): ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, searchName);
    logKeyboardInput(searchName);

    std::cout << "������ �� �������� ����������������� �����:" << std::endl;
    std::cout << "������� ����������� ������� ����������������� ����� (0-100) ��� -1 ��� ��������: ";

    while (!(std::cin >> minUnusedPercent) || (minUnusedPercent != -1 && (minUnusedPercent < 0 || minUnusedPercent > 100)) || std::cin.peek() != '\n') {
        std::cout << "������! ������� ����� �� 0 �� 100 ��� -1 ��� ��������: ";
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
        std::cout << "�� �� �������� ��������� �� �������." << std::endl;
    }
    else {
        std::cout << "=== ���������� ������ ===" << std::endl;
        std::cout << "������� ��: " << results.size() << std::endl;
        for (size_t i = 0; i < results.size(); i++) {
            const auto& cs = results[i];
            cs.displayInfo(i);
            if (cs.getNumberWork() > 0) {
                double unusedPercent = (1.0 - (double)cs.getNumberWorkOnline() / cs.getNumberWork()) * 100.0;
                std::cout << " ������� ����������������� �����: " << std::fixed << std::setprecision(1) << unusedPercent << "%" << std::endl;
            }
            else {
                std::cout << " ������� ����������������� �����: 100% (��� �����)" << std::endl;
            }
            std::cout << std::endl;
        }
    }

    std::cout << "������� Enter ��� �����������...";
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
            std::cout << "������� �����: " << it->second.getName() << " (ID: " << it->first << ")" << std::endl;
            pipes.erase(it);
        }
    }
}

void SearchPipesWithBatchOperations() {
    system("cls");
    std::cout << "=== ����� ���� �� �������� � ��������� ���������� ===" << std::endl;

    if (pipes.empty()) {
        std::cout << "������: ����� �� ���������!" << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    std::string searchName;
    int repairStatus = -1;

    std::cout << "������� �������� ����� ��� ������ (��� �������� ������ ��� ��������): ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, searchName);
    logKeyboardInput(searchName);

    std::cout << "������ �� ������� �������:" << std::endl;
    std::cout << "0 - ������ ���������� �����" << std::endl;
    std::cout << "1 - ������ ����� � �������" << std::endl;
    std::cout << "2 - ����� ������ (���������� ������)" << std::endl;
    std::cout << "�������� ������: ";

    while (!(std::cin >> repairStatus) || repairStatus < 0 || repairStatus > 2 || std::cin.peek() != '\n') {
        std::cout << "������! ������� ����� �� 0 �� 2: ";
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
        std::cout << "����� �� �������� ��������� �� �������." << std::endl;
        std::cout << "������� Enter ��� �����������...";
        std::cin.ignore(1000, '\n');
        while (std::cin.get() != '\n');
        return;
    }

    std::cout << "=== ���������� ������ ===" << std::endl;
    std::cout << "������� ����: " << results.size() << std::endl;
    for (int i = 0; i < results.size(); i++) {
        results[i].displayInfo(i);
    }

    int batchChoice;
    do {
        std::cout << "\n=== �������� �������� ===" << std::endl;
        std::cout << "1. �������� ������ ������� ��� ���� ��������� ����" << std::endl;
        std::cout << "2. ������� ��� ��������� �����" << std::endl;
        std::cout << "3. ������� ���������� ����� ��� ��������� �������" << std::endl;
        std::cout << "4. ������� ���������� ����� ��� ��������" << std::endl;
        std::cout << "0. ��������� � ������� ����" << std::endl;
        std::cout << "�������� ��������: ";

        while (!(std::cin >> batchChoice) || batchChoice < 0 || batchChoice > 4 || std::cin.peek() != '\n') {
            std::cout << "������! ������� ����� �� 0 �� 4: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            logKeyboardInput(std::to_string(batchChoice));
        }
        logKeyboardInput(std::to_string(batchChoice));

        switch (batchChoice) {
        case 1: {
            std::cout << "���������� ������ ��� ���� ��������� ����:" << std::endl;
            std::cout << "0 - ��������" << std::endl;
            std::cout << "1 - � �������" << std::endl;
            std::cout << "�������� ������: ";

            int newStatus;
            while (!(std::cin >> newStatus) || (newStatus != 0 && newStatus != 1) || std::cin.peek() != '\n') {
                std::cout << "������! ������� 0 ��� 1: ";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                logKeyboardInput(std::to_string(newStatus));
            }
            logKeyboardInput(std::to_string(newStatus));

            BatchChangePipeStatus(foundIDs, newStatus == 1);
            std::cout << "������ ������� ��� " << foundIDs.size() << " ����." << std::endl;
            break;
        }

        case 2: {
            std::cout << "�� �������, ��� ������ ������� ��� " << foundIDs.size() << " ��������� ����?" << std::endl;
            std::cout << "1 - ��, ������� ���" << std::endl;
            std::cout << "0 - ���, ��������" << std::endl;
            std::cout << "�������� ��������: ";

            int confirm;
            while (!(std::cin >> confirm) || (confirm != 0 && confirm != 1) || std::cin.peek() != '\n') {
                std::cout << "������! ������� 0 ��� 1: ";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                logKeyboardInput(std::to_string(confirm));
            }
            logKeyboardInput(std::to_string(confirm));

            if (confirm == 1) {
                BatchDeletePipes(foundIDs);
                std::cout << "������� " << foundIDs.size() << " ����." << std::endl;
                foundIDs.clear();
            }
            else {
                std::cout << "�������� ��������." << std::endl;
            }
            break;
        }

        case 3: {
            if (foundIDs.empty()) {
                std::cout << "��� ��������� ���� ��� ������." << std::endl;
                break;
            }

            std::cout << "������� ID ���� ��� ��������� ������� (����� ������): ";
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
                    std::cout << "ID " << id << " �� ������ � ����������� ������." << std::endl;
                }
            }

            if (!selectedIDs.empty()) {
                std::cout << "���������� ������ ��� ��������� ����:" << std::endl;
                std::cout << "0 - ��������" << std::endl;
                std::cout << "1 - � �������" << std::endl;
                std::cout << "�������� ������: ";

                int newStatus;
                while (!(std::cin >> newStatus) || (newStatus != 0 && newStatus != 1) || std::cin.peek() != '\n') {
                    std::cout << "������! ������� 0 ��� 1: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    logKeyboardInput(std::to_string(newStatus));
                }
                logKeyboardInput(std::to_string(newStatus));

                BatchChangePipeStatus(selectedIDs, newStatus == 1);
                std::cout << "������ ������� ��� " << selectedIDs.size() << " ����." << std::endl;
            }
            break;
        }

        case 4: {
            if (foundIDs.empty()) {
                std::cout << "��� ��������� ���� ��� ������." << std::endl;
                break;
            }

            std::cout << "������� ID ���� ��� �������� (����� ������): ";
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
                    std::cout << "ID " << id << " �� ������ � ����������� ������." << std::endl;
                }
            }

            if (!selectedIDs.empty()) {
                std::cout << "�� �������, ��� ������ ������� " << selectedIDs.size() << " ����?" << std::endl;
                std::cout << "1 - ��, �������" << std::endl;
                std::cout << "0 - ���, ��������" << std::endl;
                std::cout << "�������� ��������: ";

                int confirm;
                while (!(std::cin >> confirm) || (confirm != 0 && confirm != 1) || std::cin.peek() != '\n') {
                    std::cout << "������! ������� 0 ��� 1: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    logKeyboardInput(std::to_string(confirm));
                }
                logKeyboardInput(std::to_string(confirm));

                if (confirm == 1) {
                    BatchDeletePipes(selectedIDs);
                    std::cout << "������� " << selectedIDs.size() << " ����." << std::endl;

                    for (int id : selectedIDs) {
                        auto it = std::find(foundIDs.begin(), foundIDs.end(), id);
                        if (it != foundIDs.end()) {
                            foundIDs.erase(it);
                        }
                    }
                }
                else {
                    std::cout << "�������� ��������." << std::endl;
                }
            }
            break;
        }

        case 0:
            std::cout << "������� � ������� ����..." << std::endl;
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
                std::cout << "������ ��� ����, ��������������� ��������� ������." << std::endl;
                break;
            }
            else {
                std::cout << "\n����������� ���������� ������ (" << results.size() << " ����):" << std::endl;
                for (int i = 0; i < results.size(); i++) {
                    results[i].displayInfo(i);
                }
            }
        }

    } while (batchChoice != 0);

    std::cout << "������� Enter ��� �����������...";
    std::cin.ignore(1000, '\n');
    while (std::cin.get() != '\n');
}