#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Ticket.h"
using namespace std;

#pragma once
class User{
public:
	string login;
	string password;
	string first_name;
	string last_name;
	string passport_number;
	short is_admin;
	vector<Ticket> my_tickets;
};


class UserDao {

public:
	User getUserByLogin(string login);
	void addUser(User user);
	void deleteUser(User user);
	void updateUser(User user);

};

class Check {
public:
	int login(string login);
	int password(string password);
	int name(string name);
	int passport_number(string passport_number);
};

class RegistrationUseCase {
private:
	UserDao userDao;
public:
	RegistrationUseCase(UserDao userDao) {
		this->userDao = userDao;
	}

	int execute(string login, string password, string first_name, string last_name, string passport_number) {
		User user;
		Check check;
		if (check.login(login)) { user.login = login; }
		if (check.password(password)) { user.password = password; }
		if (check.name(first_name)) { user.first_name = first_name; }
		if (check.name(last_name)) { user.last_name = last_name; }
		if (check.passport_number(passport_number)) { user.passport_number = passport_number; }
		user.is_admin = 0;
		userDao.addUser(user);
	}
};

class LogInUseCase {
private:
	UserDao userDao;
public:
	LogInUseCase(UserDao userDao) {
		this->userDao = userDao;
	}

	User execute(string login, string password) {
		User user;
		user = userDao.getUserByLogin(login);
		if (user.password == password) {
			return user;
		}
		return;
		
		
	}
};

class ChangePasswordUseCase {

private:
	UserDao userDao;

public :
	ChangePasswordUseCase(UserDao userDao) {
		this->userDao = userDao;

	}

	void execute(User user, string newPassword) {
		
		user.password = newPassword;

		userDao.updateUser(user);

	}
};


