#include <iostream>
#include "ModulesZaritskyi.h"
using namespace std;

int main() {
    char ch;
    do {
        cout << "Введіть символ (n, v, c, x) або 'z' для виходу: ";
        cin >> ch;
        switch(ch) {
            case 'n':
                double x, y, z;
                cout << "\nEnter x: ";
                cin >> x;
                cout << "Enter y: ";
                cin >> y;
                cout << "Enter z: ";
                cin >> z;
                cout << s_calculation(x, y, z) << endl;
                break;
            case 'v': {
                double kWh;
                cout << "Введіть кількість кВт*год: ";
                cin >> kWh;
                cout << "Сума до сплати: " << calculateElectricityBill(kWh) << " грн." << endl;
                break;
            }
            case 'c': {
                double temps[12];
                cout << "Введіть 12 значень температури (°C): ";
                for (int i = 0; i < 12; i++)
                    cin >> temps[i];
                Temperature avg = calculateAverageTemperature(temps);
                cout << "Середня температура: " << avg.celsius << "°C, "
                     << avg.fahrenheit << "°F" << endl;
                break;
            }
            case 'x': {
                int N;
                cout << "Введіть число N: ";
                cin >> N;
                cout << "Результат аналізу (кількість "
                     << ((N & (1 << 10)) ? "одиниць" : "нулів")
                     << "): " << countBits(N) << endl;
                break;
            }
            default:
                cout << "\aНекоректне введення!" << endl;
                break;
        }
        cout << "Бажаєте продовжити? (введіть інший символ, крім z/Z для повторення): ";
        cin >> ch;
    } while(ch != 'z' && ch != 'Z');
    return 0;
}
