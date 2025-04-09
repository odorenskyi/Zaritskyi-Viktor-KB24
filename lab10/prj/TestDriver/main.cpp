#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>
#include "ModulesZaritskyi.h"

using namespace std;

// Структура тест-кейсу для задач 10.1
struct TestCase10_1 {
    string inputFileName;
    string outputFileName;
    string inputContent;
    string expectedOutput; // очікується точна відповідність тексту
};

// Структура тест-кейсу для задач 10.2 (порівнюємо наявність статті у тексті)
struct TestCase10_2 {
    string fileName;
    string initialContent;
    string expectedSubstring; // хоча б частина тексту, що має бути дописана
};

// Структура тест-кейсу для задач 10.3
struct TestCase10_3 {
    string outputFileName;
    double x;
    double y;
    double z;
    int b;
    string expectedSubstring; // наприклад, результат виконання s_calculation та двійкове представлення
};

// Функція зчитування вмісту файлу у рядок
string readFileContent(const string &fileName) {
    ifstream file(fileName);
    if (!file)
        return "";
    ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Функція запису логів тестування
void logTestResult(ofstream &logFile, const string &testName, const string &inputArgs,
                   const string &obtainedResult, bool passed) {
    logFile << "Test: " << testName << "\n";
    logFile << "Вхідні дані: " << inputArgs << "\n";
    logFile << "Отриманий результат:\n" << obtainedResult << "\n";
    logFile << "Статус тесту: " << (passed ? "passed" : "failed") << "\n";
    logFile << "---------------------------------------------\n";
}

int main() {
    // Відкриваємо лог-файл для протоколювання тестування
    ofstream logFile("test_log.txt", ios::out);
    if (!logFile) {
        cerr << "Не вдалося відкрити файл test_log.txt для запису логів.\n";
        return 1;
    }

    // ========================
    // ТЕСТИ ЗАДАЧІ 10.1
    // ========================
    vector<TestCase10_1> tests10_1 = {
        {
            "input_en.txt",
            "output.txt",
            "Hello world!",
            "Розробник: Віктор Заріцкий, Центральноукраїнський Національний Технічний Університет, Кропивницький, Україна, 2025.\n"
            "Мова речення: англійська\n"
            "Оброблене речення: HELLO WORLD!\n"
        },
        {
            "input_ua.txt",
            "output.txt",
            "Привіт студенте!",
            "Розробник: Віктор Заріцкий, Центральноукраїнський Національний Технічний Університет, Кропивницький, Україна, 2025.\n"
            "Мова речення: українська\n"
            "Оброблене речення: Привіт студенте!\n"
        }
        // Додаткові приклади можна додати за потребою.
    };

    for (size_t i = 0; i < tests10_1.size(); i++) {
        // Preliminary Steps: створення вхідного файлу з даними
        {
            ofstream inFile(tests10_1[i].inputFileName);
            inFile << tests10_1[i].inputContent;
            inFile.close();
        }
        // Очистка або створення вихідного файлу
        {
            ofstream outFile(tests10_1[i].outputFileName);
            outFile.close();
        }

        // Дії: виклик функції processTask10_1
        processTask10_1(tests10_1[i].inputFileName, tests10_1[i].outputFileName);

        // Отримання результату
        string obtained = readFileContent(tests10_1[i].outputFileName);
        bool passed = (obtained == tests10_1[i].expectedOutput);

        // Протоколювання
        stringstream inputArgs;
        inputArgs << "inputFileName = " << tests10_1[i].inputFileName
                  << ", outputFileName = " << tests10_1[i].outputFileName;
        logTestResult(logFile, "Task10_1 Test " + to_string(i+1), inputArgs.str(), obtained, passed);
    }

    // ========================
    // ТЕСТИ ЗАДАЧІ 10.2
    // ========================
    vector<TestCase10_2> tests10_2 = {
        {
            "input_ua.txt",
            "Привіт студенте!\n",
            R"(Стаття 62. Права осіб, які навчаються у закладах вищої освіти

1. Особи, які навчаються у закладах вищої освіти, мають право на:

1) вибір форми навчання під час вступу до закладу вищої освіти;

2) безпечні і нешкідливі умови навчання, праці та побуту;

3) трудову діяльність у позанавчальний час;

4) додаткову оплачувану відпустку у зв’язку з навчанням за основним місцем роботи, скорочений робочий час та інші пільги, передбачені законодавством для осіб, які поєднують роботу з навчанням;

5) безоплатне користування бібліотеками, інформаційними фондами, навчальною, науковою та спортивною базами закладу вищої освіти;

6) безоплатне забезпечення інформацією для навчання у доступних форматах з використанням технологій, що враховують обмеження життєдіяльності, зумовлені станом здоров’я (для осіб з особливими освітніми потребами);

7) користування виробничою, культурно-освітньою, побутовою, оздоровчою базами закладу вищої освіти у порядку, передбаченому статутом закладу вищої освіти;

8) забезпечення гуртожитком та цілодобовим доступом до нього на строк навчання у порядку, встановленому законодавством;

9) участь у науково-дослідних, дослідно-конструкторських роботах, конференціях, симпозіумах, виставках, конкурсах, представлення своїх робіт для публікації;

10) участь у заходах з освітньої, наукової, науково-дослідної, спортивної, мистецької, громадської діяльності, що проводяться в Україні та за кордоном, у встановленому законодавством порядку;

11) участь в обговоренні та вирішенні питань удосконалення навчального процесу, науково-дослідної роботи, призначення стипендій, організації дозвілля, побуту, оздоровлення;

12) внесення пропозицій щодо умов і розміру плати за навчання;

13) участь у громадських об’єднаннях;

14) участь у діяльності органів громадського самоврядування закладу вищої освіти, інститутів, факультетів, відділень, вченої ради закладу вищої освіти, органів студентського самоврядування;

15) вибір навчальних дисциплін у межах, передбачених відповідною освітньою програмою та навчальним планом, в обсязі, що становить не менш як 25 відсотків загальної кількості кредитів ЄКТС, передбачених для даного рівня вищої освіти. При цьому здобувачі певного рівня вищої освіти мають право вибирати навчальні дисципліни, що пропонуються для інших рівнів вищої освіти, за погодженням з керівником відповідного факультету чи підрозділу;

16) навчання одночасно за декількома освітніми програмами, а також у декількох закладах вищої освіти, за умови отримання тільки однієї вищої освіти за кожним ступенем за кошти державного (місцевого) бюджету;

17) академічну мобільність, у тому числі міжнародну;

18) отримання соціальної допомоги у випадках, встановлених законодавством;

19) зарахування до страхового стажу відповідно до Закону України "Про загальнообов’язкове державне пенсійне страхування" періодів навчання на денній формі навчання у закладах вищої освіти, аспірантурі, докторантурі, інтернатурі, резидентурі, за умови добровільної сплати страхових внесків;

20) академічну відпустку або перерву в навчанні із збереженням окремих прав здобувача вищої освіти, а також на поновлення навчання у порядку, встановленому центральним органом виконавчої влади у сфері освіти і науки;

21) участь у формуванні індивідуального навчального плану;

22) моральне та/або матеріальне заохочення за успіхи у навчанні, науково-дослідній і громадській роботі, за мистецькі та спортивні досягнення тощо;

23) захист від будь-яких форм експлуатації, фізичного та психічного насильства;

24) безоплатне проходження практики на підприємствах, в установах, закладах та організаціях, а також на оплату праці під час виконання виробничих функцій згідно із законодавством;

25) канікулярну відпустку тривалістю не менш як вісім календарних тижнів на навчальний рік;

26) отримання цільових пільгових державних кредитів для здобуття вищої освіти у порядку, визначеному Кабінетом Міністрів України;

27) оскарження дій органів управління закладу вищої освіти та їх посадових осіб, педагогічних і науково-педагогічних працівників;

28) спеціальний навчально-реабілітаційний супровід та вільний доступ до інфраструктури закладу вищої освіти відповідно до медико-соціальних показань за наявності обмежень життєдіяльності, зумовлених станом здоров’я.

2. Особи, які навчаються у закладах вищої освіти за денною формою навчання за рахунок коштів державного або місцевих бюджетів, мають право на отримання академічних та соціальних стипендій у встановленому законодавством порядку.

3. Особи, які навчаються у закладах вищої освіти за денною формою навчання, можуть отримувати інші стипендії, призначені фізичними (юридичними) особами.

4. Соціальні стипендії призначаються студентам (курсантам) закладу вищої освіти в порядку, встановленому Кабінетом Міністрів України.

Студенти (курсанти) закладу вищої освіти з числа дітей-сиріт та дітей, позбавлених батьківського піклування, а також студенти (курсанти) закладу вищої освіти, які в період навчання у віці від 18 до 23 років залишилися без батьків, мають гарантоване право на отримання соціальної стипендії, у тому числі у разі отримання академічної стипендії.

Академічні стипендії призначаються особам, які досягли значних успіхів у навчанні та/або науковій діяльності згідно з критеріями, встановленими Кабінетом Міністрів України. Частка студентів (курсантів), які мають право на отримання академічних стипендій, встановлюється вченою радою закладу вищої освіти у межах визначеного Кабінетом Міністрів України загального відсотка студентів (курсантів), які мають право на отримання академічних стипендій, та стипендіального фонду.

Студентам (курсантам) закладів вищої освіти, які мають право на отримання соціальної стипендії і набувають право на отримання академічної стипендії, надається один вид стипендії за їхнім вибором.

5. Розмір академічної та соціальної стипендій, порядок їх призначення і виплати встановлюються Кабінетом Міністрів України.

6. Для студентів (курсантів), які навчаються за гостродефіцитними спеціальностями (спеціалізаціями) (у галузях знань освіта, математичні, природничі, технічні науки), встановлюється підвищений розмір академічної стипендії. Перелік таких спеціальностей (спеціалізацій) та розмір підвищення визначаються Кабінетом Міністрів України.

{Частину сьому статті 62 виключено на підставі Закону № 1774-VIII від 06.12.2016}

{Частину восьму статті 62 виключено на підставі Закону № 1774-VIII від 06.12.2016}

9. Здобувачі вищої освіти, які навчаються у закладах вищої освіти за денною формою навчання, мають право на пільговий проїзд у транспорті у порядку, встановленому Кабінетом Міністрів України.

10. Студенти, курсанти закладів вищої освіти мають право на отримання студентського квитка, зразок якого затверджується центральним органом виконавчої влади у сфері освіти і науки.)"
        },
        {
            "input_en.txt",
            "HELLO WORLD!\n",
            R"(Стаття 62. Права осіб, які навчаються у закладах вищої освіти

1. Особи, які навчаються у закладах вищої освіти, мають право на:

1) вибір форми навчання під час вступу до закладу вищої освіти;

2) безпечні і нешкідливі умови навчання, праці та побуту;

3) трудову діяльність у позанавчальний час;

4) додаткову оплачувану відпустку у зв’язку з навчанням за основним місцем роботи, скорочений робочий час та інші пільги, передбачені законодавством для осіб, які поєднують роботу з навчанням;

5) безоплатне користування бібліотеками, інформаційними фондами, навчальною, науковою та спортивною базами закладу вищої освіти;

6) безоплатне забезпечення інформацією для навчання у доступних форматах з використанням технологій, що враховують обмеження життєдіяльності, зумовлені станом здоров’я (для осіб з особливими освітніми потребами);

7) користування виробничою, культурно-освітньою, побутовою, оздоровчою базами закладу вищої освіти у порядку, передбаченому статутом закладу вищої освіти;

8) забезпечення гуртожитком та цілодобовим доступом до нього на строк навчання у порядку, встановленому законодавством;

9) участь у науково-дослідних, дослідно-конструкторських роботах, конференціях, симпозіумах, виставках, конкурсах, представлення своїх робіт для публікації;

10) участь у заходах з освітньої, наукової, науково-дослідної, спортивної, мистецької, громадської діяльності, що проводяться в Україні та за кордоном, у встановленому законодавством порядку;

11) участь в обговоренні та вирішенні питань удосконалення навчального процесу, науково-дослідної роботи, призначення стипендій, організації дозвілля, побуту, оздоровлення;

12) внесення пропозицій щодо умов і розміру плати за навчання;

13) участь у громадських об’єднаннях;

14) участь у діяльності органів громадського самоврядування закладу вищої освіти, інститутів, факультетів, відділень, вченої ради закладу вищої освіти, органів студентського самоврядування;

15) вибір навчальних дисциплін у межах, передбачених відповідною освітньою програмою та навчальним планом, в обсязі, що становить не менш як 25 відсотків загальної кількості кредитів ЄКТС, передбачених для даного рівня вищої освіти. При цьому здобувачі певного рівня вищої освіти мають право вибирати навчальні дисципліни, що пропонуються для інших рівнів вищої освіти, за погодженням з керівником відповідного факультету чи підрозділу;

16) навчання одночасно за декількома освітніми програмами, а також у декількох закладах вищої освіти, за умови отримання тільки однієї вищої освіти за кожним ступенем за кошти державного (місцевого) бюджету;

17) академічну мобільність, у тому числі міжнародну;

18) отримання соціальної допомоги у випадках, встановлених законодавством;

19) зарахування до страхового стажу відповідно до Закону України "Про загальнообов’язкове державне пенсійне страхування" періодів навчання на денній формі навчання у закладах вищої освіти, аспірантурі, докторантурі, інтернатурі, резидентурі, за умови добровільної сплати страхових внесків;

20) академічну відпустку або перерву в навчанні із збереженням окремих прав здобувача вищої освіти, а також на поновлення навчання у порядку, встановленому центральним органом виконавчої влади у сфері освіти і науки;

21) участь у формуванні індивідуального навчального плану;

22) моральне та/або матеріальне заохочення за успіхи у навчанні, науково-дослідній і громадській роботі, за мистецькі та спортивні досягнення тощо;

23) захист від будь-яких форм експлуатації, фізичного та психічного насильства;

24) безоплатне проходження практики на підприємствах, в установах, закладах та організаціях, а також на оплату праці під час виконання виробничих функцій згідно із законодавством;

25) канікулярну відпустку тривалістю не менш як вісім календарних тижнів на навчальний рік;

26) отримання цільових пільгових державних кредитів для здобуття вищої освіти у порядку, визначеному Кабінетом Міністрів України;

27) оскарження дій органів управління закладу вищої освіти та їх посадових осіб, педагогічних і науково-педагогічних працівників;

28) спеціальний навчально-реабілітаційний супровід та вільний доступ до інфраструктури закладу вищої освіти відповідно до медико-соціальних показань за наявності обмежень життєдіяльності, зумовлених станом здоров’я.

2. Особи, які навчаються у закладах вищої освіти за денною формою навчання за рахунок коштів державного або місцевих бюджетів, мають право на отримання академічних та соціальних стипендій у встановленому законодавством порядку.

3. Особи, які навчаються у закладах вищої освіти за денною формою навчання, можуть отримувати інші стипендії, призначені фізичними (юридичними) особами.

4. Соціальні стипендії призначаються студентам (курсантам) закладу вищої освіти в порядку, встановленому Кабінетом Міністрів України.

Студенти (курсанти) закладу вищої освіти з числа дітей-сиріт та дітей, позбавлених батьківського піклування, а також студенти (курсанти) закладу вищої освіти, які в період навчання у віці від 18 до 23 років залишилися без батьків, мають гарантоване право на отримання соціальної стипендії, у тому числі у разі отримання академічної стипендії.

Академічні стипендії призначаються особам, які досягли значних успіхів у навчанні та/або науковій діяльності згідно з критеріями, встановленими Кабінетом Міністрів України. Частка студентів (курсантів), які мають право на отримання академічних стипендій, встановлюється вченою радою закладу вищої освіти у межах визначеного Кабінетом Міністрів України загального відсотка студентів (курсантів), які мають право на отримання академічних стипендій, та стипендіального фонду.

Студентам (курсантам) закладів вищої освіти, які мають право на отримання соціальної стипендії і набувають право на отримання академічної стипендії, надається один вид стипендії за їхнім вибором.

5. Розмір академічної та соціальної стипендій, порядок їх призначення і виплати встановлюються Кабінетом Міністрів України.

6. Для студентів (курсантів), які навчаються за гостродефіцитними спеціальностями (спеціалізаціями) (у галузях знань освіта, математичні, природничі, технічні науки), встановлюється підвищений розмір академічної стипендії. Перелік таких спеціальностей (спеціалізацій) та розмір підвищення визначаються Кабінетом Міністрів України.

{Частину сьому статті 62 виключено на підставі Закону № 1774-VIII від 06.12.2016}

{Частину восьму статті 62 виключено на підставі Закону № 1774-VIII від 06.12.2016}

9. Здобувачі вищої освіти, які навчаються у закладах вищої освіти за денною формою навчання, мають право на пільговий проїзд у транспорті у порядку, встановленому Кабінетом Міністрів України.

10. Студенти, курсанти закладів вищої освіти мають право на отримання студентського квитка, зразок якого затверджується центральним органом виконавчої влади у сфері освіти і науки.)"
        }
    };

    for (size_t i = 0; i < tests10_2.size(); i++) {
        // Preliminary Steps: створення файлу з початковим вмістом
        {
            ofstream file(tests10_2[i].fileName);
            file << tests10_2[i].initialContent;
            file.close();
        }

        // Дія: виклик processTask10_2
        processTask10_2(tests10_2[i].fileName);

        // Зчитування вмісту файлу
        string obtained = readFileContent(tests10_2[i].fileName);
        // Перевіримо чи містить отриманий текст очікуваний підрядок
        bool passed = (obtained.find(tests10_2[i].expectedSubstring) != string::npos);

        stringstream inputArgs;
        inputArgs << "fileName = " << tests10_2[i].fileName;
        logTestResult(logFile, "Task10_2 Test " + to_string(i+1), inputArgs.str(), obtained, passed);
    }

    // ========================
    // ТЕСТИ ЗАДАЧІ 10.3
    // ========================
    vector<TestCase10_3> tests10_3 = {
        {
            "output.txt", 5, 1, 2, 5,
            "Результат виконання s_calculation(5, 1, 2) = 1.20824"
            // Очікуємо рядок з "Число 10 у двійковій системі числення: 1010"
        },
        {
            "output.txt", 10, 0, -4, 1,
            "Результат виконання s_calculation(10, 0, -4) = -1.99745"
            // Очікується, що "Число 0 у двійковій системі числення: 0"
        }
    };

    for (size_t i = 0; i < tests10_3.size(); i++) {
        // Preliminary Steps: створення або очищення вихідного файлу (якщо потрібно, з попередніми даними)
        {
            ofstream outFile(tests10_3[i].outputFileName);
            // Для тестування задач 10.3 можна записати попередню інформацію, якщо вона потрібна
            outFile << "Попередній текст (як результат задач 10.1/10.2)\n";
            outFile.close();
        }

        // Дія: виклик processTask10_3
        processTask10_3(tests10_3[i].outputFileName, tests10_3[i].x, tests10_3[i].y, tests10_3[i].z, tests10_3[i].b);

        // Зчитування файлу
        string obtained = readFileContent(tests10_3[i].outputFileName);
        bool passed = (obtained.find(tests10_3[i].expectedSubstring) != string::npos);

        stringstream inputArgs;
        inputArgs << "outputFileName = " << tests10_3[i].outputFileName
                  << ", x = " << tests10_3[i].x << ", y = " << tests10_3[i].y
                  << ", z = " << tests10_3[i].z << ", b = " << tests10_3[i].b;
        logTestResult(logFile, "Task10_3 Test " + to_string(i+1), inputArgs.str(), obtained, passed);
    }

    cout << "Тестування завершено. Результати записано у файл test_log.txt.\n";
    logFile.close();
    return 0;
}
