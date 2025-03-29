#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "ModulesZaritskyi.h"

using namespace std;

// Функція 8.2.1: Вивід інформації про розробника
void getDeveloperInfo() {
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║   Заріцкий Віктор                    ║\n";
    cout << "╠═══© All rights reserved══════════════╣\n";
    cout << "╚══════════════════════════════════════╝\n";
}

// Функція 8.2.2: Обчислення логічного виразу: a+1 > |b-2|
string evaluateLogicalExpression(char a, char b) {
    return ((a + 1) > abs(b - 2)) ? "true" : "false";
}

// Функція 8.2.3: Вивід числових значень та обчислення S
void printValuesAndResult(double x, double y, double z) {
    cout << "Values (decimal): x = " << x << ", y = " << y << ", z = " << z << endl;

    // Використовуємо маніпулятори для виведення у шістнадцятковому форматі
    cout << "Values (hexadecimal): x = " << hexfloat << x
         << ", y = " << y << ", z = " << z << endl;
    cout << defaultfloat;  // Повертаємо форматування до звичайного

    double S = s_calculation(x, y, z);
    cout << "S = " << S << endl;
}

int main() {
    double x, y, z;
    char a, b;

    // Вивід інформації 8.2.1
    getDeveloperInfo();

    // Запит вхідних даних
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Enter z: ";
    cin >> z;

    cout << "Enter a (char): ";
    cin >> a;
    cout << "Enter b (char): ";
    cin >> b;

    // Вивід результату логічного виразу 8.2.2
    cout << "Logical expression (a+1 > |b-2|): " << evaluateLogicalExpression(a, b) << endl;

    // Вивід значень та обчисленого S (8.2.3)
    printValuesAndResult(x, y, z);
    return 0;
}
