#include "System.h"
#include <iostream>
#include <cmath>

void System::add_client(Client* client) {
    clients.push_back(client);
}

void System::display_all_clients() {
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

Client* System::get_client(size_t index) {
    if (index >= 0 && index < clients.size()) {
        return clients[index];
    }
    return nullptr;
}

double System::calculate_all() {
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

size_t System::get_client_count() {
    return clients.size();
}

System::~System() {
    for (auto c : clients) {
        delete c;
    }

    clients.clear();
}