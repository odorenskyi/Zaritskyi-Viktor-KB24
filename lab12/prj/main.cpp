#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <cmath>
#include <thread>
#include <chrono>
#include "ModulesZaritskyi.h"

// Структура для представлення тест-кейса
struct TestCase {
    std::string id;
    std::string action;
    std::string expectedResult;
    std::string testResult;
};

// Локальний клас для читання і обробки тест-кейсів
class TestSuiteProcessor {
private:
    std::vector<TestCase> testCases;
    std::string testSuitePath;
    std::string resultsPath;

public:
    TestSuiteProcessor(const std::string& suitePath, const std::string& outputPath)
        : testSuitePath(suitePath), resultsPath(outputPath) {}

    // Читання тест-кейсів з файлу
    bool readTestSuite() {
        std::ifstream file(testSuitePath);
        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл з тест-сьютом: " << testSuitePath << std::endl;
            return false;
        }

        std::string line;
        TestCase currentTest;
        int state = 0; // 0 - очікування ID, 1 - очікування Action, 2 - очікування Expected Result, 3 - очікування Test Result

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // Пропускаємо порожні рядки та коментарі

            if (line.find("Test Case ID:") != std::string::npos) {
                if (state > 0) {
                    testCases.push_back(currentTest);
                    currentTest = TestCase();
                }
                currentTest.id = line.substr(line.find(":") + 1);
                // Видаляємо пробіли на початку та в кінці
                size_t start = currentTest.id.find_first_not_of(" \t");
                size_t end = currentTest.id.find_last_not_of(" \t");
                if (start != std::string::npos) {
                    currentTest.id = currentTest.id.substr(start, end - start + 1);
                }
                state = 1;
            } else if (line.find("Action:") != std::string::npos && state == 1) {
                currentTest.action = line.substr(line.find(":") + 1);
                state = 2;
            } else if (line.find("Expected Result:") != std::string::npos && state == 2) {
                currentTest.expectedResult = line.substr(line.find(":") + 1);
                state = 3;
            } else if (line.find("Test Result:") != std::string::npos && state == 3) {
                currentTest.testResult = line.substr(line.find(":") + 1);
                testCases.push_back(currentTest);
                currentTest = TestCase();
                state = 0;
            }
        }

        // Додати останній тест, якщо він є
        if (state > 0) {
            testCases.push_back(currentTest);
        }

        file.close();
        return true;
    }

    // Виконання тестів
    bool runTests() {
        std::ofstream results(resultsPath);
        if (!results.is_open()) {
            std::cerr << "Не вдалося відкрити файл для запису результатів: " << resultsPath << std::endl;
            return false;
        }

        results << "Результати модульного тестування класу ClassLab12_Zaritsky\n";
        results << "=====================================================\n\n";

        int passCount = 0;
        int failCount = 0;

        // Групування тестів за категоріями
        results << "1. ТЕСТИ КОНСТРУКТОРІВ\n";
        results << "======================\n\n";
        runTestGroup(results, "TC_CONSTRUCTOR_", passCount, failCount);

        results << "\n2. ТЕСТИ ГЕТТЕРІВ\n";
        results << "==================\n\n";
        runTestGroup(results, "TC_GET_", passCount, failCount);

        results << "\n3. ТЕСТИ СЕТТЕРІВ\n";
        results << "==================\n\n";
        runTestGroup(results, "TC_SET_", passCount, failCount);

        results << "\n4. ІНТЕГРАЦІЙНІ ТЕСТИ\n";
        results << "======================\n\n";
        runTestGroup(results, "TC_INTEGRATION_", passCount, failCount);

        results << "\nПідсумок тестування:\n";
        results << "====================\n";
        results << "Всього тестів: " << testCases.size() << "\n";
        results << "Пройдено: " << passCount << "\n";
        results << "Провалено: " << failCount << "\n";
        results << "Відсоток успішності: " << (testCases.size() > 0 ? (passCount * 100.0 / testCases.size()) : 0) << "%\n";
        results << "Результат: " << (failCount == 0 ? "УСПІХ" : "ПОМИЛКА") << "\n";

        results.close();
        return failCount == 0;
    }

private:
    // Виконання групи тестів
    void runTestGroup(std::ofstream& results, const std::string& prefix, int& passCount, int& failCount) {
        for (const auto& test : testCases) {
            if (test.id.find(prefix) != std::string::npos) {
                results << "Test Case ID: " << test.id << "\n";
                results << "Action: " << test.action << "\n";
                results << "Expected Result: " << test.expectedResult << "\n";

                bool passed = executeTest(test, results);

                if (passed) {
                    results << "Test Result: PASS\n";
                    passCount++;
                } else {
                    results << "Test Result: FAIL\n";
                    failCount++;
                }
                results << "\n";
            }
        }
    }

    // Виконання окремого тесту
    bool executeTest(const TestCase& test, std::ofstream& results) {
        try {
            // ТЕСТИ КОНСТРУКТОРІВ
            if (test.id == "TC_CONSTRUCTOR_DEFAULT_001") {
                ClassLab12_Zaritsky watermelon;
                return std::abs(watermelon.getEdgeLength() - 0.2) < 0.0001;
            }
            else if (test.id == "TC_CONSTRUCTOR_DEFAULT_002") {
                ClassLab12_Zaritsky watermelon;
                return watermelon.getSkinColor() == "green";
            }
            else if (test.id == "TC_CONSTRUCTOR_DEFAULT_003") {
                ClassLab12_Zaritsky watermelon;
                return watermelon.getFleshColor() == "red";
            }
            else if (test.id == "TC_CONSTRUCTOR_DEFAULT_004") {
                ClassLab12_Zaritsky watermelon;
                return std::abs(watermelon.getRipeness() - 90.0) < 0.0001;
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_001") {
                ClassLab12_Zaritsky watermelon(0.5, "dark green", "pink", 85.5);
                return std::abs(watermelon.getEdgeLength() - 0.5) < 0.0001 &&
                       watermelon.getSkinColor() == "dark green" &&
                       watermelon.getFleshColor() == "pink" &&
                       std::abs(watermelon.getRipeness() - 85.5) < 0.0001;
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_002") {
                ClassLab12_Zaritsky watermelon(0.01, "", "", 0.0);
                return std::abs(watermelon.getEdgeLength() - 0.01) < 0.0001 &&
                       watermelon.getSkinColor() == "" &&
                       watermelon.getFleshColor() == "" &&
                       std::abs(watermelon.getRipeness() - 0.0) < 0.0001;
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_003") {
                ClassLab12_Zaritsky watermelon(10.0, "very long color name", "another long color", 100.0);
                return std::abs(watermelon.getEdgeLength() - 10.0) < 0.0001 &&
                       watermelon.getSkinColor() == "very long color name" &&
                       watermelon.getFleshColor() == "another long color" &&
                       std::abs(watermelon.getRipeness() - 100.0) < 0.0001;
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_004") {
                try {
                    ClassLab12_Zaritsky watermelon(-1.0, "green", "red", 50.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Довжина грані має бути додатним числом";
                }
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_005") {
                try {
                    ClassLab12_Zaritsky watermelon(0.0, "green", "red", 50.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Довжина грані має бути додатним числом";
                }
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_006") {
                try {
                    ClassLab12_Zaritsky watermelon(1.0, "green", "red", -10.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }
            else if (test.id == "TC_CONSTRUCTOR_PARAMS_007") {
                try {
                    ClassLab12_Zaritsky watermelon(1.0, "green", "red", 150.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }

            // ТЕСТИ ГЕТТЕРІВ
            else if (test.id == "TC_GET_EDGE_001") {
                ClassLab12_Zaritsky watermelon;
                return std::abs(watermelon.getEdgeLength() - 0.2) < 0.0001;
            }
            else if (test.id == "TC_GET_EDGE_002") {
                ClassLab12_Zaritsky watermelon(1.5, "green", "red", 50.0);
                return std::abs(watermelon.getEdgeLength() - 1.5) < 0.0001;
            }
            else if (test.id == "TC_GET_EDGE_003") {
                ClassLab12_Zaritsky watermelon(0.001, "green", "red", 50.0);
                return std::abs(watermelon.getEdgeLength() - 0.001) < 0.0001;
            }
            else if (test.id == "TC_GET_SKIN_001") {
                ClassLab12_Zaritsky watermelon;
                return watermelon.getSkinColor() == "green";
            }
            else if (test.id == "TC_GET_SKIN_002") {
                ClassLab12_Zaritsky watermelon(1.0, "yellow", "red", 50.0);
                return watermelon.getSkinColor() == "yellow";
            }
            else if (test.id == "TC_GET_SKIN_003") {
                ClassLab12_Zaritsky watermelon(1.0, "", "red", 50.0);
                return watermelon.getSkinColor() == "";
            }
            else if (test.id == "TC_GET_FLESH_001") {
                ClassLab12_Zaritsky watermelon;
                return watermelon.getFleshColor() == "red";
            }
            else if (test.id == "TC_GET_FLESH_002") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "white", 50.0);
                return watermelon.getFleshColor() == "white";
            }
            else if (test.id == "TC_GET_FLESH_003") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "very bright crimson red", 50.0);
                return watermelon.getFleshColor() == "very bright crimson red";
            }
            else if (test.id == "TC_GET_RIPENESS_001") {
                ClassLab12_Zaritsky watermelon;
                return std::abs(watermelon.getRipeness() - 90.0) < 0.0001;
            }
            else if (test.id == "TC_GET_RIPENESS_002") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "red", 0.0);
                return std::abs(watermelon.getRipeness() - 0.0) < 0.0001;
            }
            else if (test.id == "TC_GET_RIPENESS_003") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "red", 100.0);
                return std::abs(watermelon.getRipeness() - 100.0) < 0.0001;
            }
            else if (test.id == "TC_GET_RIPENESS_004") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "red", 55.75);
                return std::abs(watermelon.getRipeness() - 55.75) < 0.0001;
            }

            // ТЕСТИ getVolume()
            else if (test.id == "TC_GET_VOLUME_001") {
                ClassLab12_Zaritsky watermelon(1.0, "green", "red", 50.0);
                return std::abs(watermelon.getVolume() - 1.0) < 0.0001;
            }
            else if (test.id == "TC_GET_VOLUME_002") {
                ClassLab12_Zaritsky watermelon(2.0, "green", "red", 50.0);
                return std::abs(watermelon.getVolume() - 8.0) < 0.0001;
            }
            else if (test.id == "TC_GET_VOLUME_003") {
                ClassLab12_Zaritsky watermelon(0.5, "green", "red", 50.0);
                return std::abs(watermelon.getVolume() - 0.125) < 0.0001;
            }
            else if (test.id == "TC_GET_VOLUME_004") {
                ClassLab12_Zaritsky watermelon;
                return std::abs(watermelon.getVolume() - 0.008) < 0.0001;
            }
            else if (test.id == "TC_GET_VOLUME_005") {
                ClassLab12_Zaritsky watermelon(3.0, "green", "red", 50.0);
                return std::abs(watermelon.getVolume() - 27.0) < 0.0001;
            }
            else if (test.id == "TC_GET_VOLUME_006") {
                ClassLab12_Zaritsky watermelon(0.1, "green", "red", 50.0);
                return std::abs(watermelon.getVolume() - 0.001) < 0.0001;
            }

            // ТЕСТИ СЕТТЕРІВ
            else if (test.id == "TC_SET_EDGE_001") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setEdgeLength(1.5);
                return std::abs(watermelon.getEdgeLength() - 1.5) < 0.0001;
            }
            else if (test.id == "TC_SET_EDGE_002") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setEdgeLength(0.01);
                return std::abs(watermelon.getEdgeLength() - 0.01) < 0.0001;
            }
            else if (test.id == "TC_SET_EDGE_003") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setEdgeLength(10.0);
                return std::abs(watermelon.getEdgeLength() - 10.0) < 0.0001;
            }
            else if (test.id == "TC_SET_EDGE_FAIL_001") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setEdgeLength(-1.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Довжина грані має бути додатним числом";
                }
            }
            else if (test.id == "TC_SET_EDGE_FAIL_002") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setEdgeLength(0.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Довжина грані має бути додатним числом";
                }
            }
            else if (test.id == "TC_SET_EDGE_FAIL_003") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setEdgeLength(-100.5);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Довжина грані має бути додатним числом";
                }
            }
            else if (test.id == "TC_SET_SKIN_001") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setSkinColor("yellow");
                return watermelon.getSkinColor() == "yellow";
            }
            else if (test.id == "TC_SET_SKIN_002") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setSkinColor("");
                return watermelon.getSkinColor() == "";
            }
            else if (test.id == "TC_SET_SKIN_003") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setSkinColor("striped green and yellow");
                return watermelon.getSkinColor() == "striped green and yellow";
            }
            else if (test.id == "TC_SET_SKIN_004") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setSkinColor("green");
                watermelon.setSkinColor("yellow");
                return watermelon.getSkinColor() == "yellow";
            }
            else if (test.id == "TC_SET_FLESH_001") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setFleshColor("white");
                return watermelon.getFleshColor() == "white";
            }
            else if (test.id == "TC_SET_FLESH_002") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setFleshColor("pink");
                return watermelon.getFleshColor() == "pink";
            }
            else if (test.id == "TC_SET_FLESH_003") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setFleshColor("");
                return watermelon.getFleshColor() == "";
            }
            else if (test.id == "TC_SET_FLESH_004") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setFleshColor("deep crimson red with black seeds");
                return watermelon.getFleshColor() == "deep crimson red with black seeds";
            }
            else if (test.id == "TC_SET_RIPENESS_001") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setRipeness(50.0);
                return std::abs(watermelon.getRipeness() - 50.0) < 0.0001;
            }
            else if (test.id == "TC_SET_RIPENESS_002") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setRipeness(0.0);
                return std::abs(watermelon.getRipeness() - 0.0) < 0.0001;
            }
            else if (test.id == "TC_SET_RIPENESS_003") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setRipeness(100.0);
                return std::abs(watermelon.getRipeness() - 100.0) < 0.0001;
            }
            else if (test.id == "TC_SET_RIPENESS_004") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setRipeness(75.25);
                return std::abs(watermelon.getRipeness() - 75.25) < 0.0001;
            }
            else if (test.id == "TC_SET_RIPENESS_FAIL_001") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setRipeness(-1.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }
            else if (test.id == "TC_SET_RIPENESS_FAIL_002") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setRipeness(101.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }
            else if (test.id == "TC_SET_RIPENESS_FAIL_003") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setRipeness(-50.5);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }
            else if (test.id == "TC_SET_RIPENESS_FAIL_004") {
                ClassLab12_Zaritsky watermelon;
                try {
                    watermelon.setRipeness(200.0);
                    return false;
                } catch (const std::invalid_argument& e) {
                    return std::string(e.what()) == "Стиглість має бути в діапазоні від 0 до 100";
                }
            }

            // ІНТЕГРАЦІЙНІ ТЕСТИ
            else if (test.id == "TC_INTEGRATION_001") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setEdgeLength(2.5);
                watermelon.setSkinColor("dark green");
                watermelon.setFleshColor("bright red");
                watermelon.setRipeness(85.0);

                return std::abs(watermelon.getEdgeLength() - 2.5) < 0.0001 &&
                       watermelon.getSkinColor() == "dark green" &&
                       watermelon.getFleshColor() == "bright red" &&
                       std::abs(watermelon.getRipeness() - 85.0) < 0.0001;
            }
            else if (test.id == "TC_INTEGRATION_002") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setEdgeLength(2.0);
                double volume1 = watermelon.getVolume();
                watermelon.setEdgeLength(3.0);
                double volume2 = watermelon.getVolume();

                return std::abs(volume1 - 8.0) < 0.0001 && std::abs(volume2 - 27.0) < 0.0001;
            }
            else if (test.id == "TC_INTEGRATION_003") {
                ClassLab12_Zaritsky watermelon;
                watermelon.setSkinColor("green");
                watermelon.setSkinColor("yellow");
                watermelon.setSkinColor("red");

                return watermelon.getSkinColor() == "red";
            }
            else {
                results << "Невідомий ідентифікатор тест-кейса: " << test.id << "\n";
                return false;
            }
        }
        catch (const std::exception& e) {
            results << "Виняток під час виконання тесту: " << e.what() << "\n";
            return false;
        }
        catch (...) {
            results << "Невідомий виняток під час виконання тесту\n";
            return false;
        }
    }
};

int main() {
    system("chcp 65001 && cls");
    // Перевірка коректності розташування файлів
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string folderName = currentPath.filename().string();

    if (folderName != "prj") {
        // Вимога порушена, файл проєкту не в \Lab12\prj
        std::ofstream errorFile("TestResults.txt");
        if (errorFile.is_open()) {
            errorFile << "Встановлені вимоги порядку виконання лабораторної роботи порушено!" << std::endl;
            errorFile.close();
        }

        // Вивести 100 звукових сигналів
        for (int i = 0; i < 100; ++i) {
            std::cout << '\a'; // Звуковий сигнал
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Затримка між сигналами
        }

        return 1;
    }

    // Шляхи до файлів
    std::string testSuitePath = "../TestSuite/TestSuite.txt";
    std::string resultsPath = "../TestSuite/TestResults.txt";

    // Створення процесора тест-сьютів
    TestSuiteProcessor processor(testSuitePath, resultsPath);

    // Читання тест-сьютів
    if (!processor.readTestSuite()) {
        std::cerr << "Помилка читання тест-сьютів!" << std::endl;
        return 1;
    }

    // Запуск тестів
    bool success = processor.runTests();

    std::cout << "Тестування " << (success ? "успішно завершено" : "завершено з помилками") << std::endl;
    std::cout << "Результати записані у файл: " << resultsPath << std::endl;

    return success ? 0 : 1;
}
