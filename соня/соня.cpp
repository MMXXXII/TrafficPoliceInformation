#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <algorithm>
#include <map>
#include <ctime>
#include <limits>
#include <windows.h> // для SetConsoleOutputCP и SetConsoleCP
#include <iomanip>
#include <sstream>


using namespace std;

struct Car {
    string brand;
    int year;
    string color;
    string number;
    int registrationYear;
    string ownerLastName;
    string inspectionDate;
};

vector<Car> cars;

void showMenu() {
    cout << "Меню:\n";
    cout << "1. Добавить запись\n";
    cout << "2. Редактировать запись\n";
    cout << "3. Удалить запись\n";
    cout << "4. Вывод данных всех записей\n";
    cout << "5. Сортировка данных\n";
    cout << "6. Поиск\n";
    cout << "7. Сохранить данные в файл\n";
    cout << "8. Загрузить данные с файла\n";
    cout << "9. Очистить список\n";
    cout << "10. Вывод списка автомобилей, зарегистрированных не ранее заданного года\n";
    cout << "11. Вывод списка владельцев, просрочивших техосмотр более чем на год\n";
    cout << "12. Владелец самого старого автомобиля\n";
    cout << "13. Самая популярная марка автомобиля\n";
    cout << "14. Руководство пользователя (справка)\n";
    cout << "15. Задание\n";
    cout << "16. О программе\n";
    cout << "17. Выход\n";
}

void printCarInfo(const Car& car) {
    // Выводим информацию об автомобиле
    cout << "Марка: " << car.brand << endl;
    cout << "Год выпуска: " << car.year << endl;
    cout << "Цвет: " << car.color << endl;
    cout << "Номер автомобиля: " << car.number << endl;
    cout << "Год регистрации в ГАИ: " << car.registrationYear << endl;
    cout << "Фамилия владельца: " << car.ownerLastName << endl;
    cout << "Дата техосмотра: " << car.inspectionDate << endl;
}

void printTable(const vector<Car>& cars) {
    if (cars.empty()) {
        cout << "Вектор данных пуст." << endl;
        return;
    }

    // Определение максимальной длины для каждого столбца на основе данных
    size_t max_brand_length = 10;  // Минимальная длина для марки
    size_t max_year_length = 13;   // Минимальная длина для года выпуска
    size_t max_color_length = 13;  // Минимальная длина для цвета
    size_t max_number_length = 12;  // Минимальная длина для номера автомобиля
    size_t max_regYear_length = 13; // Минимальная длина для года регистрации
    size_t max_owner_length = 15; // Минимальная длина для фамилии владельца
    size_t max_inspDate_length = 19; // Минимальная длина для даты техосмотра

    // Нахождение максимальной длины ФИО владельца
    for (const auto& car : cars) {
        if (car.ownerLastName.length() > max_owner_length) {
            max_owner_length = car.ownerLastName.length();
        }
    }

    // Печать заголовка таблицы
    cout << "ID | " << setw(max_brand_length) << left << "Марка" << " | "
        << setw(max_year_length) << left << "Год выпуска" << " | "
        << setw(max_color_length) << left << "Цвет" << " | "
        << setw(max_number_length) << left << "Номер авто" << " | "
        << setw(max_regYear_length) << left << "Год регистрации" << " | "
        << setw(max_owner_length) << left << "Фамилия владельца" << " | "
        << setw(max_inspDate_length) << left << "Дата техосмотра" << endl;

    // Печать разделителя
    cout << setfill('-') << setw(4 + max_brand_length + max_year_length + max_color_length
        + max_number_length + max_regYear_length + max_owner_length + max_inspDate_length + 10) << "-" << endl;

    // Печать данных о машинах
    for (size_t i = 0; i < cars.size(); ++i) {
        // Форматирование года регистрации
        string regYear = to_string(cars[i].registrationYear);

        // Форматирование фамилии владельца
        string ownerLastName = cars[i].ownerLastName.empty() ? "" : cars[i].ownerLastName;

        cout << setfill(' ') << setw(2) << right << i + 1 << " | "
            << setw(max_brand_length) << left << cars[i].brand << " | "
            << setw(max_year_length) << left << cars[i].year << " | "
            << setw(max_color_length) << left << cars[i].color << " | "
            << setw(max_number_length) << left << cars[i].number << " | "
            << setw(max_regYear_length) << left << regYear << " | "
            << setw(max_owner_length) << left << ownerLastName << " | "
            << setw(max_inspDate_length) << left << cars[i].inspectionDate << endl;
    }
}



bool containsOnlyDigits(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isValidLastName(const string& lastName) {
    return regex_match(lastName, regex("[A-ZА-Я][a-zа-я]+"));
}


vector<string> validBrands = { "Toyota", "Lada", "Honda", "Mitsubishi", "Hyundai", "KIA", "BMW", "Suzuki", "Mazda", "Ford", "Lexus", "Nissan", "Renault", "Skoda", "Volkswagen", "Audi", "Jeep", "Ferrari", "Chevrolet", "Subaru" };
string validColors[] = { "красный", "черный", "серый", "зеленый", "синий", "желтый", "коричневый", "фиолетовый", "барби", "голубой", "вишневый", "белый", "оранжевый" };


void addRecord(vector<Car>& cars) {
    Car newCar;



    vector<string> validBrands = { "Toyota", "Lada", "Honda", "Mitsubishi", "Hyundai", "KIA", "BMW", "Suzuki", "Mazda", "Ford", "Lexus", "Nissan", "Renault", "Skoda", "Volkswagen", "Audi", "Jeep", "Ferrari", "Chevrolet", "Subaru" };

    cout << "Введите марку (с заглавной буквы на английском): ";
    getline(cin, newCar.brand);

    do {
        if (find(validBrands.begin(), validBrands.end(), newCar.brand) == validBrands.end()) {
            cout << "Ошибка ввода, введите корректную марку: ";
            getline(cin, newCar.brand);
        }
    } while (find(validBrands.begin(), validBrands.end(), newCar.brand) == validBrands.end());



    // Year input issue correction
    string input1;
    cout << "Введите год выпуска: ";
    bool validInput = false;
    while (!validInput) {
        cin >> input1;
        if (containsOnlyDigits(input1)) {
            try {
                int year = stoi(input1);
                if (year >= 1990 && year <= 2024) {
                    newCar.year = year; // Assign the year to the newCar object
                    validInput = true;
                }
                else {
                    cout << "Год производства должен быть не ранее 1990 и не позже 2024, введите снова: ";
                }
            }
            catch (const invalid_argument&) {
                cout << "Некорректный ввод. Введите год в числовом формате снова: ";
            }
            catch (const out_of_range&) {
                cout << "Год выпуска находится за пределами допустимого диапазона. Пожалуйста, введите снова: ";
            }
        }
        else {
            cout << "Некорректный ввод. Год должен состоять только из цифр. Пожалуйста, введите снова: ";
        }
        // Clear and ignore only if input is invalid
        if (!validInput) {
            cin.clear();
            cin.ignore();
        }
    }








    string validColors[] = { "красный", "черный", "серый", "зеленый", "синий", "желтый", "коричневый", "фиолетовый", "барби", "голубой", "вишневый", "белый", "оранжевый" };

    // Повторяем до тех пор, пока пользователь не введет правильный цвет
    bool isValidColor = false;
    cout << "Введите цвет (с маленькой буквы): ";
    do {
        cin >> newCar.color;
        isValidColor = false; // Сбрасываем значение перед каждой итерацией

        for (const string& validColor : validColors) {
            if (newCar.color == validColor) {
                isValidColor = true;
                break;
            }
        }

        if (!isValidColor) {
            cout << "Ошибка ввода, введите цвет снова: ";
        }

    } while (!isValidColor);








    regex reg3("[АВЕКМНОРСТУХ]{1}[1-9]{0,2}[1-9]{1}[АВЕКМНОРСТУХ]{2}");

    cout << "Введите номер автомобиля: ";
    cin >> newCar.number;

    while (!regex_match(newCar.number, reg3)) {
        cout << "Номер должен состоять из 1 заглавной буквы, от 1 до 3 цифр и двух заглавных букв. Введите заново: ";
        cin >> newCar.number;
    }





    cout << "Введите год регистрации в ГАИ: ";
    string input2;
    bool validInput2 = false;
    while (!validInput2) {
        cin >> input2;
        // Проверяем, содержит ли ввод только цифры
        bool onlyDigits = true;
        for (char c : input2) {
            if (!isdigit(c)) {
                onlyDigits = false;
                break;
            }
        }
        // Если ввод содержит только цифры, преобразуем его в int
        if (onlyDigits) {
            newCar.registrationYear = stoi(input2);
            // Проверяем, чтобы год был в допустимом диапазоне
            if (newCar.registrationYear >= 1990 && newCar.registrationYear <= 2024) {
                validInput2 = true;
            }
        }
        if (!validInput2) {
            cout << "Год регистрации должен быть не ранее 1990 и не позже 2024, а так же состоять из цифр. Введите снова: ";
            // Очищаем входной буфер перед повторным вводом
            cin.clear();
            cin.ignore();
        }
    }




    string input;
    cout << "Введите фамилию владельца: ";

    // Используем do-while цикл для гарантированного выполнения ввода хотя бы один раз
    do {
        cin >> input;

        if (isValidLastName(input)) {
            newCar.ownerLastName = input;
            break; // Выходим из цикла после успешного ввода
        }
        else {
            cout << "Некорректная фамилия. Пожалуйста, введите заново: ";
        }
    } while (true); // Цикл будет повторяться, пока не будет введена корректная фамилия
    cin.ignore();



    bool isValidDate = false;
    cout << "Введите дату техосмотра (дд.мм.гггг): ";
    do {
        getline(cin, newCar.inspectionDate);

        regex regB("(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.(1990|20[01234][0-9])");

        if (regex_match(newCar.inspectionDate, regB)) {
            int day = stoi(newCar.inspectionDate.substr(0, 2));
            int month = stoi(newCar.inspectionDate.substr(3, 2));
            int year = stoi(newCar.inspectionDate.substr(6, 4));

            if ((month == 2 && ((year % 4 == 0 && day > 29) || (year % 4 != 0 && day > 28))) || // Проверка февраля на число дней
                ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) ||         // Проверка месяцев с 30 днями
                (day > 31) ||                                                                      // Проверка на количество дней в месяце
                (year < 1990 || year > 2099)) {                                                    // Проверка на диапазон года
                cout << "Некорректная дата. Введите заново: ";
            }
            else {
                isValidDate = true;
            }
        }
        else {
            cout << "Некорректный ввод даты техосмотра. Введите заново: ";
        }

        cin.clear();

    } while (!isValidDate);


    bool dataEnteredCorrectly = false;
    while (!dataEnteredCorrectly) {
        cout << " " << endl;
        cout << "Вы ввели следующие данные:" << endl;
        printCarInfo(newCar);
        cout << endl;
        cout << "Данные введены верно?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;

        int choice;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cars.push_back(newCar);
            cout << "Данные успешно добавлены!" << endl;
            cout << " " << endl;
            dataEnteredCorrectly = true; 
            break;
        case 2:
            cout << "Какой пункт вы хотите изменить?" << endl;
            cout << "1. Марка" << endl;
            cout << "2. Год выпуска" << endl;
            cout << "3. Цвет" << endl;
            cout << "4. Номер автомобиля" << endl;
            cout << "5. Год регистрации в ГАИ" << endl;
            cout << "6. Фамилия владельца" << endl;
            cout << "7. Дата техосмотра" << endl;

            int subSubChoice;
            cout << "Ваш выбор: ";
            cin >> subSubChoice;
            cin.ignore();
            switch (subSubChoice) {



            case 1: {
                cout << "Введите новую марку (с заглавной буквы на английском): ";
                getline(cin, newCar.brand);
                // Проверка наличия введенной марки в списке допустимых марок
                vector<string> validBrands = { "Toyota", "Lada", "Honda", "Mitsubishi", "Hyundai", "KIA", "BMW", "Suzuki", "Mazda", "Ford", "Lexus", "Nissan", "Renault", "Skoda", "Volkswagen", "Audi", "Jeep", "Ferrari", "Chevrolet", "Subaru" };
                while (find(validBrands.begin(), validBrands.end(), newCar.brand) == validBrands.end()) {
                    cout << "Ошибка ввода, введите корректную марку: ";
                    getline(cin, newCar.brand);
                }
                break;
            }
            case 2: {
                // Ввод года выпуска с проверкой диапазона
                string input;
                cout << "Введите год выпуска: ";
                bool validInput = false;
                while (!validInput) {
                    cin >> input;
                    if (all_of(input.begin(), input.end(), ::isdigit)) {
                        try {
                            int year = stoi(input);
                            if (year >= 1990 && year <= 2024) {
                                newCar.year = year;
                                validInput = true;
                            }
                            else {
                                cout << "Год производства должен быть не ранее 1990 и не позже 2024, введите снова: ";
                            }
                        }
                        catch (...) {
                            cout << "Некорректный ввод. Введите год в числовом формате снова: ";
                        }
                    }
                    else {
                        cout << "Некорректный ввод. Год должен состоять только из цифр. Пожалуйста, введите снова: ";
                    }
                }
                break;
            }
            case 3: {
                // Ввод цвета с проверкой наличия в списке допустимых цветов
                string color;
                cout << "Введите цвет (с маленькой буквы): ";
                vector<string> validColors = { "красный", "черный", "серый", "зеленый", "синий", "желтый", "коричневый", "фиолетовый", "барби", "голубой", "вишневый", "белый", "оранжевый" };
                while (true) {
                    cin >> color;
                    if (find(validColors.begin(), validColors.end(), color) != validColors.end()) {
                        newCar.color = color;
                        break;
                    }
                    cout << "Ошибка ввода, введите цвет снова: ";
                }
                break;
            }
            case 4: {
                // Ввод номера автомобиля с проверкой формата
                string number;
                cout << "Введите номер автомобиля: ";
                regex reg("[АВЕКМНОРСТУХ]{1}[1-9]{0,2}[1-9]{1}[АВЕКМНОРСТУХ]{2}");
                while (true) {
                    cin >> number;
                    if (regex_match(number, reg)) {
                        newCar.number = number;
                        break;
                    }
                    cout << "Номер должен состоять из 1 заглавной буквы, от 1 до 3 цифр и двух заглавных букв. Введите заново: ";
                }
                break;
            }
            case 5: {
                // Ввод года регистрации в ГАИ с проверкой диапазона
                string input;
                cout << "Введите год регистрации в ГАИ: ";
                bool validInput = false;
                while (!validInput) {
                    cin >> input;
                    if (all_of(input.begin(), input.end(), ::isdigit)) {
                        try {
                            int year = stoi(input);
                            if (year >= 1990 && year <= 2024) {
                                newCar.registrationYear = year;
                                validInput = true;
                            }
                            else {
                                cout << "Год регистрации должен быть не ранее 1990 и не позже 2024, введите снова: ";
                            }
                        }
                        catch (...) {
                            cout << "Некорректный ввод. Введите год в числовом формате снова: ";
                        }
                    }
                    else {
                        cout << "Некорректный ввод. Год должен состоять только из цифр. Пожалуйста, введите снова: ";
                    }
                }
                break;
            }
            case 6: {
                // Ввод фамилии владельца
                cout << "Введите фамилию владельца: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, newCar.ownerLastName);
                // Дополнительные проверки, если необходимо
                break;
            }
            case 7: {
                // Ввод даты техосмотра с проверкой формата и допустимости даты
                string date;
                cout << "Введите дату техосмотра (дд.мм.гггг): ";
                regex reg("\\d{2}\\.\\d{2}\\.\\d{4}");
                while (true) {
                    cin >> date;
                    if (regex_match(date, reg)) {
                        newCar.inspectionDate = date;
                        break;
                    }
                    cout << "Некорректный ввод. Пожалуйста, введите дату в формате дд.мм.гггг: ";
                }
                break;
            }
            default:
                cout << "Некорректный выбор." << endl;
                break;
            }
            cout << " " << endl;
            cout << "Вы ввели следующие данные:" << endl;
            printCarInfo(newCar);
            cout << "Данные успешно сохранены!" << endl;
            cout << endl;
        default:
            cout << "Некорректный выбор." << endl;
        }
    }

}


void editRecord(vector<Car>& cars) {
    string lastNameToEdit;
    cout << "Введите фамилию владельца записи, которую вы хотите отредактировать: ";
    cin >> lastNameToEdit;

    bool found = false;
    for (auto& car : cars) {
        if (car.ownerLastName == lastNameToEdit) {
            // Проводим редактирование
            cout << "Найдена запись для редактирования. Введите новые данные:\n";

            // Редактирование марки
            cout << "Введите новую марку: ";
            getline(cin >> ws, car.brand);
            while (find(validBrands.begin(), validBrands.end(), car.brand) == validBrands.end()) {
                cout << "Ошибка ввода, введите корректную марку: ";
                getline(cin >> ws, car.brand);
            }

            // Редактирование года выпуска
            string input1;
            cout << "Введите новый год выпуска: ";
            bool validInput = false;
            while (!validInput) {
                cin >> input1;
                if (containsOnlyDigits(input1)) {
                    try {
                        int year = stoi(input1);
                        if (year >= 1990 && year <= 2024) {
                            car.year = year;
                            validInput = true;
                        }
                        else {
                            cout << "Год производства должен быть не ранее 1990 и не позже 2024, введите снова: ";
                        }
                    }
                    catch (const invalid_argument&) {
                        cout << "Некорректный ввод. Введите год в числовом формате снова: ";
                    }
                    catch (const out_of_range&) {
                        cout << "Год выпуска находится за пределами допустимого диапазона. Пожалуйста, введите снова: ";
                    }
                }
                else {
                    cout << "Некорректный ввод. Год должен состоять только из цифр. Пожалуйста, введите снова: ";
                }
                // Очищаем входной буфер перед повторным вводом
                cin.clear();
                cin.ignore();
            }

            // Редактирование цвета
            bool isValidColor = false;
            cout << "Введите новый цвет (с маленькой буквы): ";
            do {
                cin >> car.color;
                isValidColor = false;

                for (const string& validColor : validColors) {
                    if (car.color == validColor) {
                        isValidColor = true;
                        break;
                    }
                }

                if (!isValidColor) {
                    cout << "Ошибка ввода, введите цвет снова: ";
                }

            } while (!isValidColor);

            // Редактирование номера автомобиля
            regex reg3("[АВЕКМНОРСТУХ]{1}[1-9]{0,2}[1-9]{1}[АВЕКМНОРСТУХ]{2}");
            cout << "Введите новый номер автомобиля: ";
            cin >> car.number;
            while (!regex_match(car.number, reg3)) {
                cout << "Номер должен состоять из 1 заглавной буквы, от 1 до 3 цифр и двух заглавных букв. Введите заново: ";
                cin >> car.number;
            }

            // Редактирование года регистрации
            string input2;
            cout << "Введите новый год регистрации в ГАИ: ";
            bool validInput2 = false;
            while (!validInput2) {
                cin >> input2;
                if (containsOnlyDigits(input2)) {
                    try {
                        int regYear = stoi(input2);
                        if (regYear >= 1990 && regYear <= 2024) {
                            car.registrationYear = regYear;
                            validInput2 = true;
                        }
                        else {
                            cout << "Год регистрации должен быть не ранее 1990 и не позже 2024, введите снова: ";
                        }
                    }
                    catch (const invalid_argument&) {
                        cout << "Некорректный ввод. Введите год в числовом формате снова: ";
                    }
                    catch (const out_of_range&) {
                        cout << "Год регистрации находится за пределами допустимого диапазона. Пожалуйста, введите снова: ";
                    }
                }
                else {
                    cout << "Некорректный ввод. Год регистрации должен состоять только из цифр. Пожалуйста, введите снова: ";
                }
                // Очищаем входной буфер перед повторным вводом
                cin.clear();
                cin.ignore();
            }

            // Редактирование фамилии владельца
            string input;
            cout << "Введите новую фамилию владельца: ";
            cin >> input;
            while (!isValidLastName(input)) {
                cout << "Некорректная фамилия. Пожалуйста, введите заново: ";
                cin >> input;
            }
            car.ownerLastName = input;

            // Редактирование даты техосмотра
            bool isValidDate = false;
            cout << "Введите новую дату техосмотра (дд.мм.гггг): ";
            do {
                getline(cin >> ws, car.inspectionDate);
                regex regB("(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.(1990|20[01234][0-9])");

                if (regex_match(car.inspectionDate, regB)) {
                    int day = stoi(car.inspectionDate.substr(0, 2));
                    int month = stoi(car.inspectionDate.substr(3, 2));
                    int year = stoi(car.inspectionDate.substr(6, 4));

                    if ((month == 2 && ((year % 4 == 0 && day > 29) || (year % 4 != 0 && day > 28))) || // Проверка февраля на число дней
                        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) ||         // Проверка месяцев с 30 днями
                        (day > 31) ||                                                                      // Проверка на количество дней в месяце
                        (year < 1990 || year > 2099)) {                                                    // Проверка на диапазон года
                        cout << "Некорректная дата. Введите заново: ";
                    }
                    else {
                        isValidDate = true;
                    }
                }
                else {
                    cout << "Некорректный ввод даты техосмотра. Введите заново: ";
                }

            } while (!isValidDate);

            found = true; // Запись найдена и отредактирована
            break; // Выходим из цикла после редактирования
        }
    }

    if (!found) {
        cout << "Запись с фамилией владельца '" << lastNameToEdit << "' не найдена.\n";
    }
}



void deleteRecord(vector<Car>& cars, const string& surnameToDelete) {
    auto it = remove_if(cars.begin(), cars.end(), [&](const Car& car) {
        return car.ownerLastName == surnameToDelete;
        });

    if (it != cars.end()) {
        cout << "Вы уверены, что хотите удалить записи с фамилией \"" << surnameToDelete << "\"?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;

        int choice;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            cars.erase(it, cars.end());
            cout << "Записи с фамилией \"" << surnameToDelete << "\" удалены." << endl;
        }
        else {
            cout << "Удаление отменено." << endl;
        }
    }
    else {
        cout << "Записей с фамилией \"" << surnameToDelete << "\" не найдено." << endl;
    }
}

void displayRecords() {
    // Заглушка для вывода всех записей
    cout << "Вывод данных всех записей\n";
}

void sortRecords(vector<Car>& cars) {
    using namespace std;

    // Функция сравнения для сортировки по марке автомобиля
    auto compareByBrand = [](const Car& car1, const Car& car2) {
        return car1.brand < car2.brand;
        };

    // Функция сравнения для сортировки по году выпуска
    auto compareByYear = [](const Car& car1, const Car& car2) {
        return car1.year < car2.year;
        };

    // Функция сравнения для сортировки по цвету автомобиля
    auto compareByColor = [](const Car& car1, const Car& car2) {
        return car1.color < car2.color;
        };

    // Функция сравнения для сортировки по номеру автомобиля
    auto compareByNumber = [](const Car& car1, const Car& car2) {
        return car1.number < car2.number;
        };

    // Функция сравнения для сортировки по году регистрации в ГАИ
    auto compareByRegistrationYear = [](const Car& car1, const Car& car2) {
        return car1.registrationYear < car2.registrationYear;
        };

    // Функция сравнения для сортировки по фамилии владельца
    auto compareByOwnerLastName = [](const Car& car1, const Car& car2) {
        return car1.ownerLastName < car2.ownerLastName;
        };

    // Функция сравнения для сортировки по дате техосмотра
    auto compareByInspectionDate = [](const Car& car1, const Car& car2) {
        return car1.inspectionDate < car2.inspectionDate;
        };

    int choice;
    cout << "Выберите критерий сортировки:" << endl;
    cout << "1. По марке автомобиля" << endl;
    cout << "2. По году выпуска" << endl;
    cout << "3. По цвету автомобиля" << endl;
    cout << "4. По номеру автомобиля" << endl;
    cout << "5. По году регистрации в ГАИ" << endl;
    cout << "6. По фамилии владельца" << endl;
    cout << "7. По дате техосмотра" << endl;
    cin >> choice;

    // Сортировка в соответствии с выбранным критерием
    switch (choice) {
    case 1:
        sort(cars.begin(), cars.end(), compareByBrand);
        break;
    case 2:
        sort(cars.begin(), cars.end(), compareByYear);
        break;
    case 3:
        sort(cars.begin(), cars.end(), compareByColor);
        break;
    case 4:
        sort(cars.begin(), cars.end(), compareByNumber);
        break;
    case 5:
        sort(cars.begin(), cars.end(), compareByRegistrationYear);
        break;
    case 6:
        sort(cars.begin(), cars.end(), compareByOwnerLastName);
        break;
    case 7:
        sort(cars.begin(), cars.end(), compareByInspectionDate);
        break;
    default:
        cout << "Некорректный выбор. Сортировка по умолчанию по марке автомобиля." << endl;
        sort(cars.begin(), cars.end(), compareByBrand);
        break;
    }

    // Вывод отсортированных данных в виде таблицы
    printTable(cars);

    // Запрос на сохранение в файл
    cout << "Хотите сохранить отсортированные данные в файл?" << endl;
    cout << "1. Да" << endl;
    cout << "2. Нет" << endl;
    int saveChoice;
    cin >> saveChoice;
    if (saveChoice == 1) {
        string fileName;
        cout << "Введите название файла для сохранения: ";
        cin >> fileName;
        ofstream outputFile(fileName);
        if (outputFile.is_open()) {
            for (const auto& car : cars) {
                outputFile << "Марка: " << car.brand << "; ";
                outputFile << "Год выпуска: " << car.year << "; ";
                outputFile << "Цвет: " << car.color << "; ";
                outputFile << "Номер автомобиля: " << car.number << "; ";
                outputFile << "Год регистрации в ГАИ: " << car.registrationYear << "; ";
                outputFile << "Фамилия владельца: " << car.ownerLastName << "; ";
                outputFile << "Дата техосмотра: " << car.inspectionDate << ";" << endl;
            }
            cout << "Данные успешно сохранены в файл " << fileName << endl;
        }
        else {
            cout << "Ошибка открытия файла для сохранения." << endl;
        }
    }
}

void searchRecords(const vector<Car>& cars) {
    string ownerLastName;
    cout << "Введите фамилию владельца для поиска: ";
    cin >> ownerLastName;

    bool found = false;
    cout << "Результаты поиска для фамилии \"" << ownerLastName << "\":" << endl;

    // Определим, есть ли записи по данной фамилии
    vector<Car> searchResults;
    for (const auto& car : cars) {
        if (car.ownerLastName == ownerLastName) {
            searchResults.push_back(car);
            found = true;
        }
    }

    // Если записи найдены, выведем их в виде таблицы
    if (found) {
        // Определим максимальные длины для каждого столбца
        size_t max_brand_length = 10;
        size_t max_year_length = 13;
        size_t max_color_length = 13;
        size_t max_number_length = 12;
        size_t max_regYear_length = 13;
        size_t max_owner_length = 15;
        size_t max_inspDate_length = 19;

        // Найдем максимальные длины для каждого столбца
        for (const auto& car : searchResults) {
            if (car.brand.length() > max_brand_length) {
                max_brand_length = car.brand.length();
            }
            if (to_string(car.year).length() > max_year_length) {
                max_year_length = to_string(car.year).length();
            }
            if (car.color.length() > max_color_length) {
                max_color_length = car.color.length();
            }
            if (car.number.length() > max_number_length) {
                max_number_length = car.number.length();
            }
            if (to_string(car.registrationYear).length() > max_regYear_length) {
                max_regYear_length = to_string(car.registrationYear).length();
            }
            if (car.ownerLastName.length() > max_owner_length) {
                max_owner_length = car.ownerLastName.length();
            }
            if (car.inspectionDate.length() > max_inspDate_length) {
                max_inspDate_length = car.inspectionDate.length();
            }
        }

        // Печать заголовка таблицы
        cout << "ID | " << setw(max_brand_length) << left << "Марка" << " | "
            << setw(max_year_length) << left << "Год выпуска" << " | "
            << setw(max_color_length) << left << "Цвет" << " | "
            << setw(max_number_length) << left << "Номер авто" << " | "
            << setw(max_regYear_length) << left << "Год регистрации" << " | "
            << setw(max_owner_length) << left << "Фамилия владельца" << " | "
            << setw(max_inspDate_length) << left << "Дата техосмотра" << endl;

        // Печать разделителя
        cout << setfill('-') << setw(4 + max_brand_length + max_year_length + max_color_length
            + max_number_length + max_regYear_length + max_owner_length + max_inspDate_length + 10) << "-" << endl;

        // Печать данных о машинах
        int id = 1;
        for (const auto& car : searchResults) {
            cout << setfill(' ') << setw(2) << right << id++ << " | "
                << setw(max_brand_length) << left << car.brand << " | "
                << setw(max_year_length) << left << car.year << " | "
                << setw(max_color_length) << left << car.color << " | "
                << setw(max_number_length) << left << car.number << " | "
                << setw(max_regYear_length) << left << car.registrationYear << " | "
                << setw(max_owner_length) << left << car.ownerLastName << " | "
                << setw(max_inspDate_length) << left << car.inspectionDate << endl;
        }
    }
    else {
        cout << "Записи с фамилией \"" << ownerLastName << "\" не найдены." << endl;
    }
}

void saveToFile() {
    // Заглушка для сохранения данных в файл
    cout << "Сохранить данные в файл\n";
}

void loadFromFile(vector<Car>& cars) {
    string filename;
    cout << "Введите имя файла для загрузки данных (с расширением, *.txt) или введите 'отмена' для выхода в главное меню: ";
    cin >> filename;

    if (filename == "отмена") {
        cout << "Загрузка данных отменена." << endl;
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string brand, color, ownerLastName, number, inspectionDate;
        int year, registrationYear;
        char delimiter;

        if (getline(ss, brand, ';') &&
            ss >> year >> delimiter &&
            getline(ss, color, ';') &&
            getline(ss, number, ';') &&
            ss >> registrationYear >> delimiter &&
            getline(ss, ownerLastName, ';') &&
            getline(ss, inspectionDate, ';')) {

            cars.push_back({ brand, year, color, number, registrationYear, ownerLastName, inspectionDate });
        }
        else {
            cout << "Ошибка чтения строки: " << line << endl;
        }
    }

    file.close();
    cout << "Данные успешно загружены из файла." << endl;
}

void clearList() {
    // Заглушка для очистки списка
    cout << "Очистить список\n";
}

void displayCarsByYear() {
    // Заглушка для вывода списка автомобилей, зарегистрированных не ранее заданного года
    cout << "Вывод списка автомобилей, зарегистрированных не ранее заданного года\n";
}

void displayOwnersWithOverdueInspection() {
    // Заглушка для вывода списка владельцев, просрочивших техосмотр более чем на год
    cout << "Вывод списка владельцев, просрочивших техосмотр более чем на год\n";
}

void displayOldestCarOwner() {
    // Заглушка для вывода владельца самого старого автомобиля
    cout << "Владелец самого старого автомобиля\n";
}

void displayMostPopularBrand() {
    // Заглушка для вывода самой популярной марки автомобиля
    cout << "Самая популярная марка автомобиля\n";
}

void showHelp() {
    // Заглушка для руководства пользователя (справка)
    cout << "Руководство пользователя (справка)\n";
}

void showTask() {
    // Заглушка для задания
    cout << "Задание\n";
}

void aboutProgram() {
    // Заглушка для информации о программе
    cout << "О программе\n";
}

void saveOrExit() {
    // Заглушка для выхода
    cout << "Выход\n";
}

int main() {
    int choice;
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    cout << "Формирование бинарного файла. Вариант 6." << endl;

    do {
        showMenu();
        cout << "Выберите действие: ";
        if (!(cin >> choice)) {
            cout << "Ошибка: неправильный ввод. Пожалуйста, введите число от 1 до 17." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cout << endl;
        cin.ignore();

        switch (choice) {
        case 1:
            addRecord(cars);
            break;
        case 2:
            editRecord(cars);
            break;
        case 3:
        {
            string surnameToDelete;
            cout << "Введите фамилию владельца записи, которую вы хотите удалить: ";
            cin >> surnameToDelete;
            deleteRecord(cars, surnameToDelete);
        }
        break;
        case 4:
            printTable(cars);
            break;
        case 5:
            sortRecords(cars);
            break;
        case 6:
            searchRecords(cars);
            break;
        case 7:
            saveToFile();
            break;
        case 8:
            loadFromFile(cars);
            break;
        case 9:
            clearList();
            break;
        case 10:
            displayCarsByYear();
            break;
        case 11:
            displayOwnersWithOverdueInspection();
            break;
        case 12:
            displayOldestCarOwner();
            break;
        case 13:
            displayMostPopularBrand();
            break;
        case 14:
            showHelp();
            break;
        case 15:
            showTask();
            break;
        case 16:
            aboutProgram();
            break;
        case 17:
            saveOrExit();
            break;
        default:
            cout << "Ошибка: неправильный ввод. Пожалуйста, введите число от 1 до 17." << endl;
            break;
        }
    } while (choice != 17);

    return 0;
}
