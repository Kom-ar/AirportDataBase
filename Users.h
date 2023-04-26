#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#pragma once
class Users{
private:
	string login;
	string password;
	string first_name;
	string last_name;
	int passport_number;
	int is_admin;
	int balance;

public:
	int log_in(string log, string pass_w);
	int registration(string log, string passw, string first_name, string last_name, int passport_number);

};

