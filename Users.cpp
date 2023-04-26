#include "Users.h"

int Users::log_in(string log, string pass_w) {
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

int Users::registration(string log, string passw, string first_name, string last_name, string passport_number) {
	ifstream r_usr;
	ofstream w_usr;
	int ts = 0, b_letter = 0, sm_letter = 0;
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
	for (int i; i < passw.size(); i++) {
		if (passw.size() >= 6 || passw.size() <= 20) {
			if (('0' <= passw[i]) && (passw[i] <= '9')) {
				ts++;
			}
			if (('A' <= passw[i]) && (passw[i] <= 'Z')) {
				b_letter++;
			}
			if (('a' <= passw[i]) && (passw[i] <= 'z')) {
				sm_letter++;
			}
		}
	}
	if ((b_letter == 0) || (sm_letter == 0) || (ts == 0))
		return 0;

	//проверка паспортных данных
	for (int i; i < passport_number.size(); i++) {
		if (passport_number.size() == 10) {
			if (('0' > passport_number[i]) && (passport_number[i] > '9'))
				return 0;
		}
	}

	//Проверка фамилии и имени
	for (int i; i < first_name.size(); i++) {
		if (('0' <= first_name[i]) && (first_name[i] <= '9'))
			return 0;
	}
	for (int i; i < last_name.size(); i++) {
		if (('0' <= last_name[i]) && (last_name[i] <= '9'))
			return 0;
	}

	//запись данных в файл
	w_usr << log << passw << first_name << last_name << passport_number << 0;
	w_usr.close();
	return 1;
}

string Users::get_login() {
	return this->login;
}

string Users::get_password() {
	return this->password;
}

void Users::set_login(string new_login) {
	this->login = new_login;
}
void Users::set_password(string new_password) {
	this->password = new_password;
}

int Users::change_login(string new_login) {
	string old_login = get_login();
	ifstream r_usr;
	r_usr.open("Users.txt", ios::in);
	string usr_log;
	// проверка логина на уникальность
	while (!r_usr.eof()) {
		r_usr >> usr_log;
		if (usr_log == new_login) {
			r_usr.close();
			return 0;
		}
	}
	r_usr.close();
	//Изменение логина в файле Users.txt
	r_usr.open("Users.txt", ios::in);
	ofstream new_usr;
	new_usr.open("new_Users.txt", ios::out);
	while (!r_usr.eof()) {
		r_usr >> usr_log;
		if (usr_log == old_login) {
			new_usr << new_login;
			continue;
		}
		new_usr << usr_log;
	}
	r_usr.close();
	new_usr.close();

	system("del Users.txt");
	system("ren new_Users.txt Users.txt");
	set_login(new_login);
	return 1;

}

int Users::change_password(string new_password) {
	string login = get_login();
	//Проверка пароля
	int ts = 0, b_letter = 0, sm_letter = 0;
	for (int i; i < new_password.size(); i++) {
		if (new_password.size() >= 6 || new_password.size() <= 20) {
			if (('0' <= new_password[i]) && (new_password[i] <= '9')) {
				ts++;
			}
			if (('A' <= new_password[i]) && (new_password[i] <= 'Z')) {
				b_letter++;
			}
			if (('a' <= new_password[i]) && (new_password[i] <= 'z')) {
				sm_letter++;
			}
		}
	}
	if ((b_letter == 0) || (sm_letter == 0) || (ts == 0))
		return 0;

	ifstream r_usr;
	r_usr.open("Users.txt", ios::in);
	string usr_log;
	//Изменение пароля в файле Users.txt
	ofstream new_usr;
	new_usr.open("new_Users.txt", ios::out);
	while (!r_usr.eof()) {
		r_usr >> usr_log;
		if (usr_log == login) {
			new_usr << login;
			r_usr >> usr_log;
			new_usr << new_password;
			continue;
		}
		new_usr << usr_log;
	}
	r_usr.close();
	new_usr.close();

	system("del Users.txt");
	system("ren new_Users.txt Users.txt");
	set_password(new_password);
	return 1;

}