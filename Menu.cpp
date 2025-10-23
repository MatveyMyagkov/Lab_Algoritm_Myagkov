#include "Menu.h"
#include "PipelineSystem.h"
#include <windows.h>
#include <iostream>

void ShowMenu() {
    int options;
    bool flag = true;

    while (flag) {
        system("cls");
        std::cout << "���� ���������� �������������� ��������:" << std::endl;
        std::cout << "1. �������� �����" << std::endl;
        std::cout << "2. �������� ��" << std::endl;
        std::cout << "3. �������� ���� ��������" << std::endl;
        std::cout << "4. ������������� �����" << std::endl;
        std::cout << "5. ������������� ��" << std::endl;
        std::cout << "6. ���������" << std::endl;
        std::cout << "7. ���������" << std::endl;
        std::cout << "8. ������� ������ �� ID" << std::endl;
        std::cout << "9. ����� ���� �� ��������, �� �������� �� �������" << std::endl;
        std::cout << "10. ����� �� �� ��������, �� �������� ����������������� �����" << std::endl;
        std::cout << "0. �����" << std::endl;
        std::cout << "�������� ��������: ";

        while (!(std::cin >> options) || options < 0 || options > 10 || std::cin.peek() != '\n') {
            std::cout << "������! ������� ����� �� 0 �� 10: ";
            std::cin.clear();
            while (std::cin.get() != '\n');
            logKeyboardInput(std::to_string(options));
        }
        logKeyboardInput(std::to_string(options));

        switch (options) {
        case 0:
            std::cout << "���������� ������..." << std::endl;
            flag = false;
            break;
        case 1:
            Addpipe();
            std::cout << "����� ������� ���������! ����� ����: " << pipes.size() << std::endl;
            break;
        case 2:
            Addcs();
            std::cout << "�� ������� ���������! ����� ��: " << css.size() << std::endl;
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
            break;
        case 9:
            SearchPipesWithBatchOperations();
            break;
        case 10:
            SearchCS();
            break;
        }
    }
}