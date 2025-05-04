#include "Module_File_Zaritskyi.h"

bool loadDatabase(Node*& head, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Не вдалося відкрити файл для читання: " << filename << std::endl;
        return false;
    }

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;

    size_t recordCount = 0;
    file.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));

    if (file.fail()) {
        std::cout << "Помилка читання кількості записів" << std::endl;
        file.close();
        return false;
    }

    Node* current = nullptr;

    for (size_t i = 0; i < recordCount; ++i) {
        EmployeeRecord record;

        file.read(reinterpret_cast<char*>(&record.date_filled), sizeof(Date));

        file.read(reinterpret_cast<char*>(&record.employee_id), sizeof(int));

        size_t len;
        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.tax_id.resize(len);
        file.read(&record.tax_id[0], len);

        file.read(reinterpret_cast<char*>(&record.gender), sizeof(EmployeeRecord::Gender));

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.work_type.resize(len);
        file.read(&record.work_type[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.full_name.resize(len);
        file.read(&record.full_name[0], len);

        file.read(reinterpret_cast<char*>(&record.birth_date), sizeof(Date));

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.citizenship.resize(len);
        file.read(&record.citizenship[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.education.resize(len);
        file.read(&record.education[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.last_job.resize(len);
        file.read(&record.last_job[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.last_position.resize(len);
        file.read(&record.last_position[0], len);

        file.read(reinterpret_cast<char*>(&record.exp_days), sizeof(short int));
        file.read(reinterpret_cast<char*>(&record.exp_months), sizeof(short int));
        file.read(reinterpret_cast<char*>(&record.exp_years), sizeof(short int));

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.address.resize(len);
        file.read(&record.address[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.passport.resize(len);
        file.read(&record.passport[0], len);

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.notes.resize(len);
        file.read(&record.notes[0], len);

        file.read(reinterpret_cast<char*>(&record.dismissal_date), sizeof(Date));

        file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        record.dismissal_reason.resize(len);
        file.read(&record.dismissal_reason[0], len);

        if (file.fail()) {
            std::cout << "Помилка читання запису #" << i + 1 << std::endl;
            file.close();

            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            return false;
        }

        Node* newNode = new Node(record);

        if (head == nullptr) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    file.close();
    std::cout << "База даних успішно завантажена з файлу: " << filename << std::endl;
    std::cout << "Кількість завантажених записів: " << recordCount << std::endl;
    return true;
}

bool saveDatabase(Node* head, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    size_t recordCount = 0;
    Node* current = head;
    while (current != nullptr) {
        recordCount++;
        current = current->next;
    }

    file.write(reinterpret_cast<const char*>(&recordCount), sizeof(recordCount));

    current = head;
    while (current != nullptr) {
        EmployeeRecord record = current->record;

        file.write(reinterpret_cast<const char*>(&record.date_filled), sizeof(Date));

        file.write(reinterpret_cast<const char*>(&record.employee_id), sizeof(int));

        size_t len = record.tax_id.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.tax_id.c_str(), len);

        file.write(reinterpret_cast<const char*>(&record.gender), sizeof(EmployeeRecord::Gender));

        len = record.work_type.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.work_type.c_str(), len);

        len = record.full_name.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.full_name.c_str(), len);

        file.write(reinterpret_cast<const char*>(&record.birth_date), sizeof(Date));

        len = record.citizenship.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.citizenship.c_str(), len);

        len = record.education.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.education.c_str(), len);

        len = record.last_job.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.last_job.c_str(), len);

        len = record.last_position.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.last_position.c_str(), len);

        file.write(reinterpret_cast<const char*>(&record.exp_days), sizeof(short int));
        file.write(reinterpret_cast<const char*>(&record.exp_months), sizeof(short int));
        file.write(reinterpret_cast<const char*>(&record.exp_years), sizeof(short int));

        len = record.address.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.address.c_str(), len);

        len = record.passport.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.passport.c_str(), len);

        len = record.notes.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.notes.c_str(), len);

        file.write(reinterpret_cast<const char*>(&record.dismissal_date), sizeof(Date));

        len = record.dismissal_reason.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        file.write(record.dismissal_reason.c_str(), len);

        current = current->next;
    }

    if (file.fail()) {
        std::cout << "Помилка запису даних у файл" << std::endl;
        file.close();
        return false;
    }

    file.close();
    std::cout << "База даних успішно збережена у файл: " << filename << std::endl;
    std::cout << "Кількість збережених записів: " << recordCount << std::endl;
    return true;
}
