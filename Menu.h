#pragma once
#include"UserOperation.h"
using namespace std;
// º¯ÊıÉùÃ÷
void save();
void reload();
void login();
void showMenu(const User& user);
void userMenu(const User& user);
void librarianMenu(const User& user);
void adminMenu(const User& user);
void back(bool isBack = true );

