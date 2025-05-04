#include <iostream>
#include <cctype>
#include "Module_SearchDel_Kolesnyk.h"

using namespace std;

string toLower(const string& str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if ((c & 0xF0) == 0xD0 || (c & 0xF0) == 0xD1) {
            if (i + 1 < str.size()) {
                unsigned char next = str[i + 1];
                if (c == 0xD0 && next >= 0x80 && next <= 0x8F) {
                    result += c;
                    result += next + 0x20;
                } else if (c == 0xD0 && next >= 0x90 && next <= 0xAF) {
                    result += c;
                    result += next + 0x20;
                } else if (c == 0xD1 && next >= 0x80 && next <= 0x8F) {
                    result += c;
                    result += next + 0x20;
                } else {
                    result += c;
                    result += next;
                }
                ++i;
            }
        } else {
            if (isupper(c)) {
                result += tolower(c);
            } else {
                result += c;
            }
        }
    }
    return result;
}

void printFoundRecord(const EmployeeRecord& record, int index) {
    cout << "\n--- Знайдений запис #" << index << " ---" << endl;
    cout << "Табельний номер: " << record.employee_id << endl;
    cout << "ПІБ: " << record.full_name << endl;
    cout << "Ідентифікаційний номер: " << record.tax_id << endl;
    cout << "Дата заповнення: " << record.date_filled.toString() << endl;
    cout << "Стать: " << genderToString(record.gender) << endl;
    cout << "Вид роботи: " << record.work_type << endl;
    cout << "Дата народження: " << record.birth_date.toString() << endl;
    cout << "Громадянство: " << record.citizenship << endl;
    cout << "Освіта: " << record.education << endl;
    cout << "Останнє місце роботи: " << record.last_job << endl;
    cout << "Остання посада: " << record.last_position << endl;
    cout << "Стаж роботи: " << record.exp_years << " років, "
         << record.exp_months << " місяців, "
         << record.exp_days << " днів" << endl;
    cout << "Місце проживання: " << record.address << endl;
    cout << "Паспортні дані: " << record.passport << endl;
    cout << "Додаткові відомості: " << record.notes << endl;

    if (!record.dismissal_date.isEmpty()) {
        cout << "Дата звільнення: " << record.dismissal_date.toString() << endl;
        cout << "Причина звільнення: " << record.dismissal_reason << endl;
    } else {
        cout << "Статус: Працює" << endl;
    }
    cout << "------------------------" << endl;
}

bool findRecordByName(Node* head, const string& name) {
    if (head == nullptr) {
        cout << "База даних порожня." << endl;
        return false;
    }

    string searchName = toLower(name);
    Node* current = head;
    int count = 0;
    int index = 1;

    cout << "\n=== Результати пошуку за '" << name << "' ===" << endl;

    while (current != nullptr) {
        string currentName = toLower(current->record.full_name);
        if (currentName.find(searchName) != string::npos) {
            printFoundRecord(current->record, index);
            count++;
        }
        current = current->next;
        index++;
    }

    if (count == 0) {
        cout << "Записів з прізвищем '" << name << "' не знайдено." << endl;
        return false;
    } else {
        cout << "Знайдено записів: " << count << endl;
        return true;
    }
}

bool deleteRecord(Node*& head, int employee_id) {
    if (head == nullptr) {
        cout << "База даних порожня." << endl;
        return false;
    }

    if (head->record.employee_id == employee_id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Запис з табельним номером " << employee_id << " успішно видалено." << endl;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->record.employee_id != employee_id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Запис з табельним номером " << employee_id << " успішно видалено." << endl;
        return true;
    } else {
        cout << "Запис з табельним номером " << employee_id << " не знайдено." << endl;
        return false;
    }
}
