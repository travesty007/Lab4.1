#ifndef SYSTEM_H
#define SYSTEM_H

#include "Client.h"
#include <vector>

class System {
    std::vector<Client*> clients;
public:
    void add_client(Client* client);
    void display_all_clients();
    Client* get_client(size_t index);
    double calculate_all();
    size_t get_client_count();
    ~System();
};

#endif