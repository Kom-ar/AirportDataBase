#include "Users.h"

User UserDao::getUserByLogin(string login) {
	ifstream usr_f;
	User user;
	usr_f.open("Users.txt", ios::in);
	string usr_log;
	while (!usr_f.eof()) {
		usr_f >> usr_log;
		if (usr_log == login) {
			user.login = usr_log;
			usr_f >> usr_log;
			user.password = usr_log;
			usr_f >> usr_log;
			user.first_name = usr_log;
			usr_f >> usr_log;
			user.last_name = usr_log;
			usr_f >> usr_log;
			user.passport_number = usr_log;
			usr_f >> usr_log;
			user.is_admin = stoi(usr_log);
			usr_f.close();
			return user;
		}
	}
	usr_f.close();
	return; //?
}

void UserDao::addUser(User user) {
	ofstream usr_f;
	usr_f.open("Users.txt", ios::app);
	usr_f << user.login << user.password << user.first_name << user.last_name << user.passport_number << user.is_admin;
	usr_f.close();
}

void UserDao::deleteUser(User user) {
	ifstream r_usr;
	r_usr.open("Users.txt", ios::in);
	string usr_log;
	ofstream new_usr;
	new_usr.open("new_Users.txt", ios::out);
	while (!r_usr.eof()) {
		r_usr >> usr_log;
		if (usr_log == user.login) {
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			continue;
		}
		new_usr << usr_log;
	}
	r_usr.close();
	new_usr.close();

	system("del Users.txt");
	system("ren new_Users.txt Users.txt");
}

void UserDao::updateUser(User user) {
	ifstream r_usr;
	r_usr.open("Users.txt", ios::in);
	string usr_log;
	ofstream new_usr;
	new_usr.open("new_Users.txt", ios::out);
	while (!r_usr.eof()) {
		r_usr >> usr_log;
		if (usr_log == user.login) {
			new_usr << user.login << user.password << user.first_name << user.last_name << user.passport_number << user.is_admin;
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			r_usr >> usr_log;
			continue;
		}
		new_usr << usr_log;
	}
	r_usr.close();
	new_usr.close();

	system("del Users.txt");
	system("ren new_Users.txt Users.txt");
}

int Check::login(string login) {
	ifstream usr_f;
	usr_f.open("Users.txt", ios::in);
	string usr_log;
	if (((('A' <= login[0]) && (login[0] <= 'Z')) || (('a' <= login[0]) && (login[0] <= 'z')) && (login.size() >= 4 || login.size() <= 15))) {
		//Проверка на уникальность
		while (!usr_f.eof()) {
			usr_f >> usr_log;
			if (usr_log == login) {
				usr_f.close();
				return 0;
			}
		}
		usr_f.close();
		return 1;
	}
	return 0;
	

}

int Check::passport_number(string passport_number) {
	//проверка паспортных данных
	for (int i = 0; i < passport_number.size(); i++) {
		if (passport_number.size() == 10) {
			if (('0' > passport_number[i]) && (passport_number[i] > '9'))
				return 0;
		}
	}
	return 1;
}

int Check::name(string name) {
	//Проверка фамилии и имени
	for (int i = 0; i < name.size(); i++) {
		if (('0' <= name[i]) && (name[i] <= '9'))
			return 0;
	}
	return 1;
}


int Check::password(string password) {
	//Проверка пароля(от 6 до 20 символов, как минимум 1 цифра, 1 маленькая и 1 большая буква
	int ts = 0, b_letter = 0, sm_letter = 0;
	for (int i = 0; i < password.size(); i++) {
		if (password.size() >= 6 || password.size() <= 20) {
			if (('0' <= password[i]) && (password[i] <= '9')) {
				ts++;
			}
			if (('A' <= password[i]) && (password[i] <= 'Z')) {
				b_letter++;
			}
			if (('a' <= password[i]) && (password[i] <= 'z')) {
				sm_letter++;
			}
		}
	}
	if ((b_letter > 0) && (sm_letter > 0) && (ts > 0))
		return 1;
	return 0;

}