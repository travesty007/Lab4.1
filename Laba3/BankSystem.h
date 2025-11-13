#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Client.h"
#include <string>

// Функции для безопасного ввода
int safe_input_int(const std::string& prompt);
std::string safe_input_string(const std::string& prompt);
std::string check(int rate, int amount);

// Функции меню
void display_menu();
int safe_menu_input();
void add_client_menu(class System* system, short is_vip);
void copy_client_menu(class System* system);

Client* make_client(std::string name, int rate, int amount, short vip);

#endif