#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class User {
private:
	string login;
	string password;
	string first_name;
	string last_name;
	int passport_number;
	int is_admin;
	int balance;

public:
	int log_in(string log, string pass_w) {
		ifstream usr_f;
		usr_f.open("Users.txt", ios::in);
		string usr_log;
		while (!usr_f.eof()) {
			usr_f >> usr_log;
			if (usr_log == log) {
				string usr_passw;
				usr_f >> usr_passw;
				if (usr_passw == pass_w) {
					usr_f.close();
					return 1;
				}
				usr_f.close();
				return 0;
			}
		}
		usr_f.close();
		return 0;

	}

	int registration(string log, string passw, string first_name, string last_name, int passport_number) {
		ifstream r_usr;
		ofstream w_usr;
		r_usr.open("Users.txt", ios::in);
		w_usr.open("Users.txt", ios::app);
		// проверка логина на уникальность
		string usr_log;
		while (!r_usr.eof()) {
			r_usr >> usr_log;
			if (usr_log == log) {
				r_usr.close();
				w_usr.close();
				return 0;
			}
		}
		r_usr.close();

		// проверка пароля
		// проверка фамиилии, имени, паспортных данных

		//запись данных в файл
		w_usr << log << passw << first_name << last_name << passport_number << 0;
		w_usr.close();
		return 1;
	}
};