#include "Menu.h"
#include "PipelineSystem.h"
#include <windows.h>
#include <iostream>

void ShowMenu() {
    int options;
    bool flag = true;

    while (flag) {
        system("cls");
        std::cout << "Меню управления трубопроводной системой:" << std::endl;
        std::cout << "1. Добавить трубу" << std::endl;
        std::cout << "2. Добавить КС" << std::endl;
        std::cout << "3. Просмотр всех объектов" << std::endl;
        std::cout << "4. Редактировать трубу" << std::endl;
        std::cout << "5. Редактировать КС" << std::endl;
        std::cout << "6. Сохранить" << std::endl;
        std::cout << "7. Загрузить" << std::endl;
        std::cout << "8. Удалить объект по ID" << std::endl;
        std::cout << "9. Поиск труб по названию, по признаку «в ремонте»" << std::endl;
        std::cout << "10. Поиск КС по названию, по проценту незадействованных цехов" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";

        while (!(std::cin >> options) || options < 0 || options > 10 || std::cin.peek() != '\n') {
            std::cout << "Ошибка! Введите число от 0 до 10: ";
            std::cin.clear();
            while (std::cin.get() != '\n');
            logKeyboardInput(std::to_string(options));
        }
        logKeyboardInput(std::to_string(options));

        switch (options) {
        case 0:
            std::cout << "Завершение работы..." << std::endl;
            flag = false;
            break;
        case 1:
            Addpipe();
            std::cout << "Труба успешно добавлена! Всего труб: " << pipes.size() << std::endl;
            break;
        case 2:
            Addcs();
            std::cout << "КС успешно добавлена! Всего КС: " << css.size() << std::endl;
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