#ifndef MODULESZARITSKYI_H_INCLUDED
#define MODULESZARITSKYI_H_INCLUDED

struct Temperature {
    double celsius;
    double fahrenheit;
};


double s_calculation(double x, double y, double z);
double calculateElectricityBill(double kWh);
Temperature calculateAverageTemperature(const double temps[12]);
int countBits(int N);

#endif // MODULESZARITSKYI_H_INCLUDED
