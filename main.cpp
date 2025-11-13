#include <windows.h>
#include <iostream>
#include "Menu.h"

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ShowMenu();
    return 0;
}
// To do
// Template щаблон проверок
// Перегрузка операторов cin / cout
// cout << pipe
