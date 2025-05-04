#ifndef STRUCT_TYPE_PROJECT_2_H_INCLUDED
#define STRUCT_TYPE_PROJECT_2_H_INCLUDED

#include <string>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool isEmpty() const {
        return day == 0 && month == 0 && year == 0;
    }
    string toString() const {
        if (isEmpty()) return "-";
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
};

struct EmployeeRecord {
    Date date_filled;                          // Дата заповнення
    int employee_id;                           // Табельний номер
    string tax_id;                             // Ідентифікаційний номер
    enum class Gender { M, F, Other } gender;  // Стать
    string work_type;                          // Вид роботи (основна, за сумісництвом)
    string full_name;                          // ПІБ працівника
    Date birth_date;                           // Дата народження
    string citizenship;                        // Громадянство
    string education;                          // Освіта
    string last_job;                           // Останнє місце роботи
    string last_position;                      // Остання посада
    short int exp_days, exp_months, exp_years; // Стаж роботи (днів/місяців/років)
    string address;                            // Місце проживання
    string passport;                           // Паспортні дані
    string notes;                              // Додаткові відомості
    Date dismissal_date;                       // Дата звільнення
    string dismissal_reason;                   // Причина звільнення
    EmployeeRecord() :
        employee_id(0),
        gender(Gender::Other),
        exp_days(0),
        exp_months(0),
        exp_years(0) {}
};

struct Node {
    EmployeeRecord record;
    Node* next;
    Node(EmployeeRecord rec) : record(rec), next(nullptr) {}
};

inline string genderToString(EmployeeRecord::Gender gender) { //вбудована функція, яка не визначає ту саму функцію більше одного разу
    switch (gender) {
        case EmployeeRecord::Gender::M: return "Чоловіча";
        case EmployeeRecord::Gender::F: return "Жіноча";
        default: return "Інше";
    }
}

#endif // STRUCT_TYPE_PROJECT_2_H_INCLUDED
