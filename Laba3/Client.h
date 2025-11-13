#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <iomanip>

class Client {
public:
    std::string name;
    int rate;
    int amount;

    Client(std::string name, int rate, int amount);
    virtual ~Client() = default;

    virtual void displayInfo() = 0;
    Client& operator=(const Client& other);
    virtual void clone(Client* client) = 0;
    double calculate();
};

class VIPClient : virtual public Client {
public:
    VIPClient(std::string name, int rate, int amount);
    void clone(Client* client) override;
    void displayInfo() override;
};

class Simple_Client : virtual public Client {
public:
    Simple_Client(std::string name, int rate, int amount);
    void clone(Client* client) override;
    void displayInfo() override;
};

class SuperVIPClient : public VIPClient, public Simple_Client {
public:
    SuperVIPClient(std::string name, int rate, int amount);
    void clone(Client* client) override;
    void displayInfo() override;
};

#endif