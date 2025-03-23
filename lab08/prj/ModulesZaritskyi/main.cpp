#include <cmath>

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
