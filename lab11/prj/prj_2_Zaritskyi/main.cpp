#include <iostream>
#include <string>
#include <limits>

#include "struct_type_project_2.h"
#include "Module_File_Zaritskyi.h"
#include "Module_CRUD_Kondratenko.h"
#include "Module_SearchDel_Kolesnyk.h"

const std::string DATABASE_FILENAME = "employee_database.bin";

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseExecution() {
    std::cout << "\nНатисніть Enter для продовження...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    clearScreen();
    std::cout << "=== Відділ кадрів: особова картка працівника ===\n" << std::endl;
    std::cout << "1. Переглянути всю базу даних на екрані" << std::endl;
    std::cout << "2. Вивести базу даних у текстовий файл" << std::endl;
    std::cout << "3. Додати новий запис" << std::endl;
    std::cout << "4. Пошук запису за прізвищем" << std::endl;
    std::cout << "5. Видалити запис за табельним номером" << std::endl;
    std::cout << "0. Вихід" << std::endl;
    std::cout << "\nВиберіть опцію: ";
}

int main() {
#ifdef _WIN32
    system("chcp 65001");
    system("cls");
#endif

    Node* head = nullptr;

    loadDatabase(head, DATABASE_FILENAME);

    int choice;

    do {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некоректне введення. Спробуйте ще раз." << std::endl;
            pauseExecution();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Переглянути всю базу
            {
                clearScreen();
                std::cout << "=== Перегляд бази даних ===" << std::endl;
                printAllRecords(head);
                pauseExecution();
                break;
            }
            case 2: // Вивести базу в текстовий файл
            {
                clearScreen();
                std::cout << "=== Виведення бази даних у файл ===" << std::endl;
                std::string filename;
                std::cout << "Введіть ім'я файлу для виведення: ";
                std::getline(std::cin, filename);
                if (filename.empty()) {
                    filename = "output.txt";
                }
                printAllRecords(head, true, filename);
                pauseExecution();
                break;
            }
            case 3: // Додати новий запис
            {
                clearScreen();
                addRecord(head);
                pauseExecution();
                break;
            }
            case 4: // Пошук за прізвищем
            {
                clearScreen();
                std::cout << "=== Пошук за прізвищем ===" << std::endl;
                std::string name;
                std::cout << "Введіть прізвище або частину ПІБ для пошуку: ";
                std::getline(std::cin, name);
                if (!name.empty()) {
                    findRecordByName(head, name);
                } else {
                    std::cout << "Пошуковий запит не може бути порожнім." << std::endl;
                }
                pauseExecution();
                break;
            }
            case 5: // Видалити запис
            {
                clearScreen();
                std::cout << "=== Видалення запису ===" << std::endl;
                int id;
                std::cout << "Введіть табельний номер працівника для видалення: ";
                if (std::cin >> id) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    deleteRecord(head, id);
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некоректний табельний номер." << std::endl;
                }
                pauseExecution();
                break;
            }
            case 0: // Вихід
            {
                std::cout << "Збереження бази даних перед виходом..." << std::endl;
                saveDatabase(head, DATABASE_FILENAME);
                std::cout << "Дякуємо за використання програми!" << std::endl;
                break;
            }
            default:
            {
                std::cout << "Невідома опція. Спробуйте ще раз." << std::endl;
                pauseExecution();
                break;
            }
        }
    } while (choice != 0);

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
