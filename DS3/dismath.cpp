#include "calculator.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool isValidInput(const string& input) {
    int count = input.find_first_not_of(' ');
    string s = input.substr(count);
    
    if (s.length() > 9 || (s.length() > 8 && s[0] != '-')) {
        return false;
    }

    
    if (input[0] == '-') {
        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] < 'a' || input[i] > 'h') {
                return false;
            }
        }
    }
    else {
        
        for (size_t i = 0; i < input.length(); ++i) {
            if (input[i] < 'a' || input[i] > 'h') {
                return false;
            }
        }
    }

    return true;
}


int main() {
    setlocale(LC_ALL, "rus");

    Calculator calc;
    string str1, str2;
    char operation;
    int choice;

    do {
        cout << "Калькулятор <большой> конечной арифметики" << endl;
        cout << "Введите первую строку: ";
        while (true) {
            cin >> str1;
            if (isValidInput(str1)) {
                break;  
            }
            else {
                cout << "Некорректный ввод. Пожалуйста, введите строку, состоящую только из букв a-h, длиной до 8 символов (или до 9, если начинается с '-'). Попробуйте снова: ";
            }
        }

        cout << "Введите вторую строку: ";
        while (true) {
            cin >> str2;
            if (isValidInput(str2)) {
                break;  
            }
            else {
                cout << "Некорректный ввод. Пожалуйста, введите строку, состоящую только из букв a-h, длиной до 8 символов " << endl << "(или до 9, если начинается с '-').Попробуйте снова : ";
            }
        }

        
        cout << "\nВыберите операцию:\n";
        cout << "1. Сложение \n";
        cout << "2. Вычитание \n";
        cout << "3. Умножение \n";
        cout << "4. Деление \n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        cin.ignore();

        
        if (choice == 0) {
            cout << "Выход из программы...\n";
            break;
        }

        
        switch (choice) {
        case 1:
            operation = '+';
            break;
        case 2:
            operation = '-';
            break;
        case 3:
            operation = '*';
            break;
        case 4:
            operation = '/';
            break;
        default:
            cout << "Некорректный выбор!" << endl;
            continue;
        }

        
        cout << calc.evaluate(str1, str2, operation) << endl;

        cout << "Нажмите Enter для продолжения...";
        cin.get();  

        system("cls");

    } while (choice != 0);  

    return 0;
}
