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

#ifndef MODULES_ZARITSKY_H
#define MODULES_ZARITSKY_H

#include <string>
#include <cmath>
#include <stdexcept>

// Клас, що представляє абстракцію кавуна кубічної форми
class ClassLab12_Zaritsky {
private:
    double edgeLength;    // Довжина грані куба (м)
    std::string skinColor; // Колір шкірки кавуна
    std::string fleshColor; // Колір м'якоті кавуна
    double ripeness;      // Стиглість кавуна (%)

public:
    // Конструктор за замовчуванням
    ClassLab12_Zaritsky();

    ClassLab12_Zaritsky(double edge, std::string skin, std::string flesh, double ripe);

    // Отримання довжини грані куба
    double getEdgeLength() const;

    // Отримання кольору шкірки
    std::string getSkinColor() const;

    // Отримання кольору м'якоті
    std::string getFleshColor() const;

    // Отримання рівня стиглості
    double getRipeness() const;

    // Обчислення об'єму куба
    double getVolume() const;

    // Встановлення довжини грані куба
    void setEdgeLength(double edge);

    // Встановлення кольору шкірки
    void setSkinColor(std::string skin);

    // Встановлення кольору м'якоті
    void setFleshColor(std::string flesh);

    // Встановлення рівня стиглості
    void setRipeness(double ripe);
};

inline ClassLab12_Zaritsky::ClassLab12_Zaritsky()
    : edgeLength(0.2), skinColor("green"), fleshColor("red"), ripeness(90.0) {
}

inline ClassLab12_Zaritsky::ClassLab12_Zaritsky(double edge, std::string skin, std::string flesh, double ripe) {
    setEdgeLength(edge);
    setSkinColor(skin);
    setFleshColor(flesh);
    setRipeness(ripe);
}

inline double ClassLab12_Zaritsky::getEdgeLength() const {
    return edgeLength;
}

inline std::string ClassLab12_Zaritsky::getSkinColor() const {
    return skinColor;
}

inline std::string ClassLab12_Zaritsky::getFleshColor() const {
    return fleshColor;
}

inline double ClassLab12_Zaritsky::getRipeness() const {
    return ripeness;
}

inline double ClassLab12_Zaritsky::getVolume() const {
    return pow(edgeLength, 3);
}

inline void ClassLab12_Zaritsky::setEdgeLength(double edge) {
    if (edge <= 0) {
        throw std::invalid_argument("Довжина грані має бути додатним числом");
    }
    edgeLength = edge;
}

inline void ClassLab12_Zaritsky::setSkinColor(std::string skin) {
    skinColor = skin;
}

inline void ClassLab12_Zaritsky::setFleshColor(std::string flesh) {
    fleshColor = flesh;
}

inline void ClassLab12_Zaritsky::setRipeness(double ripe) {
    if (ripe < 0 || ripe > 100) {
        throw std::invalid_argument("Стиглість має бути в діапазоні від 0 до 100");
    }
    ripeness = ripe;
}

#endif // MODULESZARITSKYI_H_INCLUDED
