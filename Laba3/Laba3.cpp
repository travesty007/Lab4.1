#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <Windows.h>
#include <iomanip>
#include <cmath>

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

class Client {
public:
    std::string name;
    int rate;
    int amount;

    Client(std::string name, int rate, int amount) : name(name), rate(rate), amount(amount) {}

    virtual void displayInfo() = 0;

    Client& operator=(const Client& counter) {
        if (&counter != this) {
            name = counter.name;
            rate = counter.rate;
            amount = counter.amount;
        }
        return *this;
    }

    double calculate() {
        return rate * amount / 100;
    }

    virtual ~Client() = default;
};

class VIPClient : virtual public Client {
public:

    VIPClient(std::string name, int rate, int amount) : Client(name, rate, amount + 10000) {}

    void displayInfo() override {
        std::cout << "VIP Клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
            << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
    }
};

class Simple_Client : virtual public Client {
public:

    Simple_Client(std::string name, int rate, int amount) : Client(name, rate, amount + 1000) {}

    void displayInfo() override {
        std::cout << "Обычный клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
            << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
    }
};

class SuperVIPClient : public VIPClient, public Simple_Client {
public:
    SuperVIPClient(std::string name, int rate, int amount) : Client(name, rate, amount + 11000), VIPClient(name, rate, amount), Simple_Client(name, rate, amount) {};

    void displayInfo() override {
        std::cout << "Супер клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
            << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
    }
};

class System {
    std::vector<Client*> clients;
public:
    void add_client(Client* client) {
        clients.push_back(client);
    }
    void add_client(Client client) {
        clients.push_back(&client);
    }

    void display_all_clients() {
        if (clients.empty()) {
            std::cout << "Нет клиентов в системе.\n";
            return;
        }

        std::cout << "\n=== СПИСОК КЛИЕНТОВ ===\n";
        for (size_t i = 0; i < clients.size(); i++) {
            std::cout << i + 1 << ". ";
            clients[i]->displayInfo();
        }
    }

    double calculate_all() {
        long double result = 0;

        for (auto c : clients) {
            long double client_income = (*c).calculate();

            if (std::isinf(client_income) || std::isnan(client_income)) {
                std::cout << "Ошибка: переполнение при расчете дохода клиента!" << std::endl;
                return -1;
            }

            result += client_income;

            if (std::isinf(result) || std::isnan(result)) {
                std::cout << "Ошибка: переполнение при суммировании общего дохода!" << std::endl;
                return -1;
            }
        }

        return result;
    }

    size_t get_client_count() {
        return clients.size();
    }

    ~System() {
        for (auto c : clients) {
            delete c;
        }
    }
};

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

void display_menu() {
    std::cout << "\n=== БАНКОВСКАЯ СИСТЕМА ===\n";
    std::cout << "1. Добавить обычного клиента\n";
    std::cout << "2. Добавить VIP клиента\n";
    std::cout << "3. Добавить Super клиента\n";
    std::cout << "4. Показать всех клиентов\n";
    std::cout << "5. Рассчитать общий доход\n";
    std::cout << "6. Выйти\n";
    std::cout << "Выберите опцию: ";
}

int safe_menu_input() {
    int choice;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка! Пожалуйста, введите число от 1 до 6: ";
        }
        else {
            if (std::cin.peek() != '\n') {
                std::cout << "Ошибка! Введите только число от 1 до 6: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            std::cin.ignore(10000, '\n');
            if (choice >= 1 && choice <= 6) {
                return choice;
            }
            else {
                std::cout << "Неверный выбор. Введите число от 1 до 6: ";
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
            std::cout << "Выход из программы...\n";
            break;
        }

    } while (choice != 5);

    delete system;
    return 0;
}