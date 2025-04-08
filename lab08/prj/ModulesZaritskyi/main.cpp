#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>
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

// Допоміжна функція: перетворення рядка у верхній регістр (англійське речення)
std::string convertToUppercase(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Допоміжна функція: перевірка, чи символ є латинською буквою
bool isLatinLetter(char c) {
    return ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') );
}

// Допоміжна функція: визначення мови речення
// Якщо кількість латинських символів перевищує кількість інших алфавітних символів,
// вважаємо, що мова – англійська; інакше – українська.
std::string determineLanguage(const std::string &s) {
    int latinCount = 0;
    int otherLetterCount = 0;
    for (char c : s) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            if (isLatinLetter(c))
                latinCount++;
            else
                otherLetterCount++;
        }
    }
    return (latinCount > otherLetterCount) ? "англійська" : "українська";
}

// Допоміжна функція: видалення заборонених слів із українського речення
// Заборонені слова: "лінощі", "сесія", "академзаборгованість"
std::string removeForbiddenWords(const std::string &s) {
    std::string result = s;
    // Перелік заборонених слів (можна розширювати за потребою; регістр порівнюємо у нижньому)
    const std::string forbiddenWords[] = {"лінощі", "сесія", "академзаборгованість"};

    // Для спрощення обробки переводимо текст у нижній регістр для пошуку,
    // але при видаленні з оригінального тексту працюємо зі знайденими позиціями.
    std::string lowerResult = s;
    std::transform(lowerResult.begin(), lowerResult.end(), lowerResult.begin(), ::tolower);

    // Для кожного забороненого слова виконуємо пошук і видалення
    for (const std::string &word : forbiddenWords) {
        size_t pos = lowerResult.find(word);
        while (pos != std::string::npos) {
            // Видалення слова з оригінального рядка
            result.erase(pos, word.length());
            // Також з нижнього рядка – для коректності пошуку наступного входження
            lowerResult.erase(pos, word.length());
            pos = lowerResult.find(word);
        }
    }
    return result;
}

// Допоміжна функція: перетворення десяткового числа у двійковий рядок
std::string convertToBinary(int num) {
    if (num == 0)
        return "0";
    std::string binaryRepresentation;
    while (num > 0) {
        binaryRepresentation.insert(binaryRepresentation.begin(), (num % 2) + '0');
        num /= 2;
    }
    return binaryRepresentation;
}

// Реалізація задачі 10.1
// Функція читає вхідний файл, визначає мову тексту, обробляє речення та записує результати у вихідний файл.
void processTask10_1(const std::string &inputFileName, const std::string &outputFileName) {
    std::ifstream inFile(inputFileName);
    if (!inFile) {
        std::cerr << "Помилка: не вдалося відкрити файл для читання: " << inputFileName << std::endl;
        return;
    }

    std::string sentence;
    std::getline(inFile, sentence);
    inFile.close();

    // Визначення мови речення
    std::string language = determineLanguage(sentence);
    std::string processedSentence;
    if (language == "англійська") {
        processedSentence = convertToUppercase(sentence);
    } else {
        processedSentence = removeForbiddenWords(sentence);
    }

    // Відкриття вихідного файлу для запису (створення/очищення)
    std::ofstream outFile(outputFileName);
    if (!outFile) {
        std::cerr << "Помилка: не вдалося відкрити файл для запису: " << outputFileName << std::endl;
        return;
    }

    // Запис даних: авторська інформація, мова речення, оброблене речення
    outFile << "Розробник: Віктор Заріцкий, Центральноукраїнський Національний Технічний УніверсИТЕТ, Кропивницький, Україна, 2025.\n";
    outFile << "Мова речення: " << language << "\n";
    outFile << "Оброблене речення: " << processedSentence << "\n";
    outFile.close();
}

// Реалізація задачі 10.2
// Функція дозаписує до заданого файлу текст статті 62 Закону України "Про вищу освіту" та поточну дату й час.
void processTask10_2(const std::string &inputFileName) {
    // Відкриття файлу у режимі дозапису
    std::ofstream file(inputFileName, std::ios::app);
    if (!file) {
        std::cerr << "Помилка: не вдалося відкрити файл для дозапису: " << inputFileName << std::endl;
        return;
    }

    // Текст статті 62 Закону України "Про вищу освіту"
    const std::string textArticle = "Текст статті 62: [тут вставити текст статті 62 Закону України 'Про вищу освіту']\n";

    // Отримання поточного часу
    std::time_t now = std::time(nullptr);
    std::string currentTime = std::ctime(&now); // ctime повертає рядок з символом нового рядка в кінці

    // Дописування інформації до файлу
    file << textArticle;
    file << "Дата та час дозапису: " << currentTime;
    file.close();
}

// Реалізація задачі 10.3
// Функція викликає s_calculation для заданих чисел, перетворює число y до двійкового формату та дозаписує результати до вихідного файлу.
void processTask10_3(const std::string &outputFileName, int x, int y, int z, int b) {
    // Виклик функції s_calculation з модуля ModulesZaritsky
    int resultCalculation = s_calculation(x, y, z);

    // Перетворення числа y до двійкового формату
    std::string binaryY = convertToBinary(y);

    // Відкриття вихідного файлу для дозапису
    std::ofstream outFile(outputFileName, std::ios::app);
    if (!outFile) {
        std::cerr << "Помилка: не вдалося відкрити файл для дозапису: " << outputFileName << std::endl;
        return;
    }

    // Запис результатів числових обчислень
    outFile << "Результат виконання s_calculation(" << x << ", " << y << ", " << z << ") = " << resultCalculation << "\n";
    outFile << "Число " << y << " у двійковій системі числення: " << binaryY << "\n";
    outFile.close();
}
