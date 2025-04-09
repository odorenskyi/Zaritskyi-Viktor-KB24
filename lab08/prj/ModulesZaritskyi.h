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
void processTask10_1(const std::string &inputFileName, const std::string &outputFileName);
void processTask10_2(const std::string &inputFileName);
void processTask10_3(const std::string &outputFileName, double x, double y, double z, int b);

#endif // MODULESZARITSKYI_H_INCLUDED
