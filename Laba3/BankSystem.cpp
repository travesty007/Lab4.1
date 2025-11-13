#include "BankSystem.h"
#include "Client.h"
#include "System.h"
#include <iostream>
#include <iostream>
#include <limits>
#include <Windows.h>

int safe_input_int(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка! Пожалуйста, введите число.\n";
        }
        else {
            if (std::cin.peek() != '\n') {
                std::cout << "Ошибка! Введите только число.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

std::string safe_input_string(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);

    if (!value.empty() && value.back() == '\r') {
        value.pop_back();
    }

    return value;
}

std::string check(int rate, int amount) {
    if (rate <= 0) {
        return "Ставка должна быть положительной";
    }
    else if (rate > 100) {
        return "Ставка не может быть больше 100%";
    }
    else if (amount <= 0) {
        return "Размер вклада должен быть положительным";
    }
    else if (amount >= 10000000) {
        return "Вклад слишком большой";
    }
    else {
        return "Норм";
    }
}

void display_menu() {
    std::cout << "\n=== БАНКОВСКАЯ СИСТЕМА ===\n";
    std::cout << "1. Добавить обычного клиента\n";
    std::cout << "2. Добавить VIP клиента\n";
    std::cout << "3. Добавить Super клиента\n";
    std::cout << "4. Показать всех клиентов\n";
    std::cout << "5. Рассчитать общий доход\n";
    std::cout << "6. Создать копию клиента\n";
    std::cout << "7. Выйти\n";
    std::cout << "Выберите опцию: ";
}

int safe_menu_input() {
    int choice;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка! Пожалуйста, введите число от 1 до 7: ";
        }
        else {
            if (std::cin.peek() != '\n') {
                std::cout << "Ошибка! Введите только число от 1 до 7: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            std::cin.ignore(10000, '\n');
            if (choice >= 1 && choice <= 7) {
                return choice;
            }
            else {
                std::cout << "Неверный выбор. Введите число от 1 до 7: ";
            }
        }
    }
}

void add_client_menu(System* system, short is_vip) {
    std::string name = safe_input_string("Введите имя клиента: ");
    int rate = safe_input_int("Введите ставку (%): ");
    int amount = safe_input_int("Введите сумму вклада: ");

    Client* client = make_client(name, rate, amount, is_vip);
    if (client != nullptr) {
        system->add_client(client);
    }
}

void copy_client_menu(System* system) {
    if (system->get_client_count() == 0) {
        std::cout << "Нет клиентов для копирования.\n";
        return;
    }

    system->display_all_clients();

    int client_index = safe_input_int("Введите номер клиента для копирования: ") - 1;

    Client* original = system->get_client(client_index);
    if (original == nullptr) {
        std::cout << "Неверный номер клиента!\n";
        return;
    }

    std::string new_name = safe_input_string("Введите новое имя для копии: ");

    Client* copy = nullptr;

    if (dynamic_cast<SuperVIPClient*>(original)) {
        copy = new SuperVIPClient("", 0, 0);
    }
    else if (dynamic_cast<VIPClient*>(original)) {
        copy = new VIPClient("", 0, 0);
    }
    else if (dynamic_cast<Simple_Client*>(original)) {
        copy = new Simple_Client("", 0, 0);
    }

    /*if (copy) {
        copy->clone(original);

        copy->name = new_name;

        system->add_client(copy);
        std::cout << "Копия клиента успешно создана!\n";
    }*/
    if (copy) {
        *copy = *original;

        copy->name = new_name;

        system->add_client(copy);
        std::cout << "Копия клиента успешно создана!\n";
    }
    else {
        std::cout << "Ошибка при создании копии клиента!\n";
    }
}

Client* make_client(std::string name, int rate, int amount, short vip) {
    std::string result = check(rate, amount);
    if (result == "Норм") {
        std::cout << "Клиент " + name + " успешно создан\n";
        if (vip == 2) {
            return new SuperVIPClient(name, rate, amount);
        }
        else if (vip == 1) {
            return new VIPClient(name, rate, amount);
        }
        else {
            return new Simple_Client(name, rate, amount);
        }
    }
    else {
        std::cout << result << std::endl;
        return nullptr;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    System* system = new System();
    int choice;

    std::cout << "Добро пожаловать в банковскую систему!\n";

    do {
        display_menu();
        choice = safe_menu_input();

        switch (choice) {
        case 1:
            add_client_menu(system, 0);
            break;

        case 2:
            add_client_menu(system, 1);
            break;

        case 3:
            add_client_menu(system, 2);
            break;

        case 4:
            system->display_all_clients();
            break;

        case 5:
            if (system->get_client_count() > 0) {
                std::cout << "\nОбщая сумма дохода по всем вкладам: "
                    << system->calculate_all() << std::endl;
            }
            else {
                std::cout << "\nНет клиентов для расчета.\n";
            }
            break;

        case 6:
            copy_client_menu(system);
            break;

        case 7:
            std::cout << "Выход из программы...\n";
            break;
        }

    } while (choice != 7);

    delete system;
    return 0;
}