#include "Module_CRUD_Kondratenko.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>


using namespace std;

Date inputDate(const string& prompt, bool allowEmpty = false) {
    Date date;
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (allowEmpty && input.empty()) {
            return Date();
        }

        if (sscanf(input.c_str(), "%d.%d.%d", &date.day, &date.month, &date.year) == 3) {
            if (date.day >= 1 && date.day <= 31 && date.month >= 1 && date.month <= 12 && date.year >= 1900) {
                return date;
            }
        }
        cout << "Некоректний формат дати. Використовуйте формат ДД.ММ.РРРР" << endl;
    }
}

template<typename T>
T getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некоректне введення. Спробуйте ще раз." << endl;
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

bool isEmployeeIdUnique(Node* head, int employee_id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->record.employee_id == employee_id) {
            return false;
        }
        current = current->next;
    }
    return true;
}

bool addRecord(Node*& head) {
    cout << "\n=== Додавання нового запису ===\n" << endl;

    EmployeeRecord newRecord;

    newRecord.date_filled = inputDate("Дата заповнення (ДД.ММ.РРРР): ");
    while (true) {
        int id = getInput<int>("Табельний номер: ");
        if (isEmployeeIdUnique(head, id)) {
            newRecord.employee_id = id;
            break;
        } else {
            cout << "Такий табельний номер вже існує. Введіть інший." << endl;
        }
    }
    newRecord.tax_id = getStringInput("Ідентифікаційний номер: ");

    string gender_input;
    while (true) {
        cout << "Стать (ч/ж/інше): ";
        getline(cin, gender_input);
        if (gender_input == "ч" || gender_input == "Ч") {
            newRecord.gender = EmployeeRecord::Gender::M;
            break;
        } else if (gender_input == "ж" || gender_input == "Ж") {
            newRecord.gender = EmployeeRecord::Gender::F;
            break;
        } else if (gender_input == "інше" || gender_input == "Інше") {
            newRecord.gender = EmployeeRecord::Gender::Other;
            break;
        } else {
            cout << "Некоректне введення. Використовуйте 'ч', 'ж' або 'інше'." << endl;
        }
    }

    string work_type_input;
    while (true) {
        cout << "Вид роботи (основна/за сумісництвом): ";
        getline(cin, work_type_input);
        if (work_type_input == "основна" || work_type_input == "за сумісництвом") {
            newRecord.work_type = work_type_input;
            break;
        } else {
            cout << "Некоректне введення. Використовуйте 'основна' або 'за сумісництвом'." << endl;
        }
    }

    newRecord.full_name = getStringInput("ПІБ працівника: ");
    newRecord.birth_date = inputDate("Дата народження (ДД.ММ.РРРР): ");
    newRecord.citizenship = getStringInput("Громадянство: ");
    newRecord.education = getStringInput("Освіта: ");
    newRecord.last_job = getStringInput("Останнє місце роботи: ");
    newRecord.last_position = getStringInput("Остання посада: ");

    newRecord.exp_days = getInput<short int>("Стаж роботи (днів): ");
    newRecord.exp_months = getInput<short int>("Стаж роботи (місяців): ");
    newRecord.exp_years = getInput<short int>("Стаж роботи (років): ");

    newRecord.address = getStringInput("Місце проживання: ");
    newRecord.passport = getStringInput("Паспортні дані: ");
    newRecord.notes = getStringInput("Додаткові відомості: ");

    while (true) {
    string dismissal_input;
    cout << "Чи звільнений працівник? (так/ні): ";
    getline(cin, dismissal_input);
    if (dismissal_input == "так" || dismissal_input == "Так") {
        newRecord.dismissal_date = inputDate("Дата звільнення (ДД.ММ.РРРР): ");
        newRecord.dismissal_reason = getStringInput("Причина звільнення: ");
        break;
    } else if (dismissal_input == "ні" || dismissal_input == "Ні") {
        break;
    } else {
        cout << "Некоректне введення. Використовуйте 'так' або 'ні'." << endl;
    }
}

    Node* newNode = new Node(newRecord);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    cout << "\nЗапис успішно додано до бази даних.\n" << endl;
    return true;
}

void printRecord(ostream& out, const EmployeeRecord& record, int index) {
    out << "--- Запис #" << index << " ---" << endl;
    out << "Табельний номер: " << record.employee_id << endl;
    out << "Дата заповнення: " << record.date_filled.toString() << endl;
    out << "ПІБ: " << record.full_name << endl;
    out << "Ідентифікаційний номер: " << record.tax_id << endl;
    out << "Стать: " << genderToString(record.gender) << endl;
    out << "Вид роботи: " << record.work_type << endl;
    out << "Дата народження: " << record.birth_date.toString() << endl;
    out << "Громадянство: " << record.citizenship << endl;
    out << "Освіта: " << record.education << endl;
    out << "Останнє місце роботи: " << record.last_job << endl;
    out << "Остання посада: " << record.last_position << endl;
    out << "Стаж роботи: " << record.exp_years << " років, "
        << record.exp_months << " місяців, "
        << record.exp_days << " днів" << endl;
    out << "Місце проживання: " << record.address << endl;
    out << "Паспортні дані: " << record.passport << endl;
    out << "Додаткові відомості: " << record.notes << endl;

    if (!record.dismissal_date.isEmpty()) {
        out << "Дата звільнення: " << record.dismissal_date.toString() << endl;
        out << "Причина звільнення: " << record.dismissal_reason << endl;
    } else {
        out << "Статус: Працює" << endl;
    }
    out << "------------------------" << endl;
}

bool printAllRecords(Node* head, bool toFile, const string& filename) {
    if (head == nullptr) {
        cout << "База даних порожня." << endl;
        return false;
    }

    ofstream file;
    if (toFile) {
        file.open(filename);
        if (!file.is_open()) {
            cout << "Не вдалося відкрити файл для запису: " << filename << endl;
            return false;
        }
    }

    ostream& out = toFile ? file : cout;

    out << "\n=== База даних співробітників ===\n" << endl;

    Node* current = head;
    int index = 1;
    while (current != nullptr) {
        printRecord(out, current->record, index++);
        current = current->next;
    }

    if (toFile) {
        file.close();
        cout << "Дані успішно виведені у файл: " << filename << endl;
    }

    return true;
}
