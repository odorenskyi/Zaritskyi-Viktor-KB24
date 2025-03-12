#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ModulesZaritskyi.h"

using namespace std;

string doubleToString(double value, int precision = 5) {
    ostringstream oss;
    oss << fixed << setprecision(precision) << value;
    return oss.str();
}

void test_s_calculation() {
    double x[10] = {5.0, 4.1, 10.0, 6.0, 100.0, 4.0001, 3.9, -5.0, 7.5, 50.0};
    double y[10] = {1.0, 0.0, 0.0, 3.0, 2.0, 5.0, 1.0, 0.0, 0.0, 1.0};
    double z[10] = {2.0, 0.0, -4.0, 10.0, 20.0, 5.0, 10.0, 0.0, 0.0, -10.0};
    double expected_results[10] = {1.20824, 3.68345, -1.99745, 13.46949, 13.90284, 8.77684, NAN, NAN, 4.00157, 2.44739};

    for (short i = 0; i < 10; i++) {
        double result = s_calculation(x[i], y[i], z[i]);
        string resultStr = doubleToString(result);
        string expectedStr = doubleToString(expected_results[i]);
        bool passed = false;

        // Для NaN використовується isNaN, оскільки NaN != NaN
        if (std::isnan(result) && std::isnan(expected_results[i])) {
            passed = true;
        } else if (resultStr == expectedStr) {
            passed = true;
        }

        cout << "Test case #" << i+1 << ": s_calculation("
             << x[i] << ", " << y[i] << ", " << z[i] << ") = "
             << resultStr << " == " << expectedStr
             << " --> " << (passed ? "passed" : "failed") << endl;
    }
}

int main() {
    test_s_calculation();
    return 0;
}
