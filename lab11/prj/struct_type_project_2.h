#ifndef STRUCT_TYPE_PROJECT_2_H_INCLUDED
#define STRUCT_TYPE_PROJECT_2_H_INCLUDED

#include <string>
#include <chrono>

using namespace std;

struct EmployeeRecord {
    chrono::year_month_day date_filled;         // Дата заповнення
    int employee_id;                            // Табельний номер
    string tax_id;                              // Ідентифікаційний номер
    enum class Gender { M, F, Other } gender;   // Стать
    string work_type;                           // Вид роботи
    string full_name;                           // ПІБ працівника
    chrono::year_month_day birth_date;          // Дата народження
    string citizenship;                         // Громадянство
    string education;                           // Освіта
    string last_job;                            // Останнє місце роботи
    string last_position;                       // Остання посада
    short int exp_days, exp_months, exp_years;  // Стаж роботи (днів/місяців/років)
    string address;                             // Місце проживання
    string passport;                            // Паспортні дані
    string notes;                               // Додаткові відомості
    chrono::year_month_day dismissal_date;      // Дата звільнення
    string dismissal_reason;                    // Причина звільнення
};

struct Node {
    EmployeeRecord record;
    Node* next;
};

#endif // STRUCT_TYPE_PROJECT_2_H_INCLUDED
