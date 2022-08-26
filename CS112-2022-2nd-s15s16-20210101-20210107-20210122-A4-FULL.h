#pragma once
#include <string>

using namespace std;

void get_user();
void get_mail();
bool not_valid_user(string x);
void get_pass();
void get_phone();
bool not_valid_pass(string pass);
string hide_pass();
void login();
void change_password();
