#include <iostream>
#include "ModulesZaritskyi.h"

using namespace std;

void run_tests() {
    // Тестування задачі 9.1
    int task1_input[3] = {100, 150, 1000};
    double task1_expected[3] = {13.0843, 19.62645, 534.047};

    cout << "Тестування задачі 9.1" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 3; i++) {
        double result = calculateElectricityBill(task1_input[i]);
        cout << "Аргумент(-и): " << task1_input[i] << " kWh" << endl
             << "Очікується: " << task1_expected[i] << endl
             << "Отримано: " << result
             << (abs(result - task1_expected[i]) < 0.001 ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }

    // Тестування задачі 9.2
    double task2_input[3][12] = {
        {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0},
        {-5.0, -3.0, 0.0, 5.0, 10.0, 15.0, 20.0, 18.0, 12.0, 7.0, 0.0, -2.0},
        {25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0},
    };
    Temperature task2_expected[3] = {
        {5.5, 41.9},
        {6.4167, 43.55},
        {25, 77}
    };

    cout << "Тестування задачі 9.2" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 3; i++) {
        Temperature result = calculateAverageTemperature(task2_input[i]);
        cout << "Аргумент(-и): ";
        for (int j = 0; j < 12; j++) {
            cout << task2_input[i][j];
            if (j < 11) {
                cout << ", ";
            }
        }
        cout << endl;
        cout << "Очікується: " << task2_expected[i].celsius << " °C, " << task2_expected[i].fahrenheit << " °F;" << endl
             << "Отримано: " << result.celsius << " °C, " << result.fahrenheit << " °F"
             << (abs(result.celsius - task2_expected[i].celsius) < 0.01 &&
                 abs(result.fahrenheit - task2_expected[i].fahrenheit) < 0.01 ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }

    // Тестування задачі 9.3
    int task3_input[3] = {100, 1024, 0};
    int task3_expected[3] = {4, 1, 1};

    cout << "Тестування задачі 9.3" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 3; i++) {
        int result = countBits(task3_input[i]);
        cout << "Аргумент(-и): " << task3_input[i] << endl
             << "Очікується: " << task3_expected[i] << endl
             << "Отримано: " << result
             << (result == task3_expected[i] ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }
}

int main() {
    run_tests();
    return 0;
}
