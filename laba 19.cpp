#include <iostream>
#include "Header.h"

int main() {
    using namespace std;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do {
        cout << "   ЛАБОРАТОРНАЯ РАБОТА №19\n";
        cout << "1. Задача 1: Код Хэмминга\n";
        cout << "2. Задача 2: Код Хаффмана\n";
        cout << "3. Задача 3: Шифр Морзе\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Ошибка ввода!\n";
            continue;
        }

        switch (choice) {
        case 1: Hamming15(); break;
        case 2: Huffman1(); break;
        case 3: Morse3(); break;
        case 0: cout << "Программа завершена.\n"; break;
        default: cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}

