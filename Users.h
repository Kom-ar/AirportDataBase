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
	string passport_number;
	string is_admin;
	int balance;

public:
	int log_in(string log, string pass_w);
	int registration(string log, string passw, string first_name, string last_name, string passport_number);
	string get_login();
	string get_password();
	void set_login(string new_login);
	void set_password(string new_password);
	int change_login(string new_login);
	int change_password(string new_password);


};

