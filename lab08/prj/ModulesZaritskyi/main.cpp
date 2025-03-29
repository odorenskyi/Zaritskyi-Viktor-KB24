#include <cmath>
#include "ModulesZaritskyi.h"

using namespace std;

double s_calculation(double x, double y, double z) {
    // Перевірка області визначення: x має бути більше 4, щоб логарифм був додатнім.
    if (x <= 4.0) {
        return NAN; // або можна сигналізувати про помилку іншим способом
    }

    double logValue = log10(x - 3.0);
    // Якщо логарифм не додатній, обчислення неможливе
    if (logValue <= 0.0) {
        return NAN;
    }

    // Обчислення виразу під квадратним коренем
    double underSqrt = (12.0 * x * x) / logValue;
    // Перевірка, що підкореневий вираз не від'ємний
    if (underSqrt < 0.0) {
        return NAN;
    }

    // Обчислення S згідно з формулою
    double result = pow(3.0 * sin(sqrt(underSqrt)), 2.0) + 0.5 * z;

    return result;
}

double calculateElectricityBill(double kWh) {
    double rate;
    if (kWh <= 150)
        rate = 0.130843;
    else if (kWh <= 800)
        rate = 0.241945;
    else
        rate = 0.534047;
    return kWh * rate;
}

Temperature calculateAverageTemperature(const double temps[12]) {
    double sum = 0.0;
    for (int i = 0; i < 12; i++) {
        sum += temps[i];
    }
    double avgC = sum / 12.0;
    Temperature result;
    result.celsius = avgC;
    result.fahrenheit = 32 + (9.0 / 5.0) * avgC;
    return result;
}


int countBits(int N) {
    if (N == 0) {
        return 1;
    }
    bool bit10 = (N & (1 << 10)) != 0;
    int count = 0;
    while (N > 0) {
        int bit = N & 1;
        // Якщо bit10 == false – підраховуємо нулі, інакше одиниці.
        count += (bit10 ? (bit == 1 ? 1 : 0) : (bit == 0 ? 1 : 0));
        N >>= 1;
    }
    return count;
}
