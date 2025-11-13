#include "Client.h"

Client::Client(std::string name, int rate, int amount)
    : name(name), rate(rate), amount(amount) {}

Client& Client::operator=(const Client& other) {
    if (&other != this) {
        name = other.name;
        rate = other.rate;
        amount = other.amount;
    }
    return *this;
}

double Client::calculate() {
    return rate * amount / 100;
}

// VIPClient implementation
VIPClient::VIPClient(std::string name, int rate, int amount)
    : Client(name, rate, amount + 10000) {}

void VIPClient::clone(Client* client) {
    name = client->name;
    rate = client->rate;
    amount = client->amount;
}

void VIPClient::displayInfo() {
    std::cout << "VIP Клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
        << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
}

Simple_Client::Simple_Client(std::string name, int rate, int amount)
    : Client(name, rate, amount + 1000) {}

void Simple_Client::clone(Client* client) {
    name = client->name;
    rate = client->rate;
    amount = client->amount;
}

void Simple_Client::displayInfo() {
    std::cout << "Обычный клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
        << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
}

SuperVIPClient::SuperVIPClient(std::string name, int rate, int amount)
    : Client(name, rate, amount + 11000), VIPClient(name, rate, amount), Simple_Client(name, rate, amount) {}

void SuperVIPClient::clone(Client* client) {
    name = client->name;
    rate = client->rate;
    amount = client->amount;
}

void SuperVIPClient::displayInfo() {
    std::cout << "Супер клиент: " << name << ", Ставка: " << rate << "%, Вклад: " << amount
        << ", Доход: " << std::fixed << std::setprecision(2) << calculate() << std::endl;
}