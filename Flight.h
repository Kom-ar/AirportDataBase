#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#pragma once
using namespace std;

typedef struct {
	string year;
	string month;
	string day;
	string hour;
	string minutes;
}DATE;

class Seats {
private:
	string type;
	string seat_number;
	string user_login;
};

class Flight{
public:
	string flight_number;
	DATE departure_date;
	DATE arrival_date;
	string departure_town;
	string arrival_town;
	string flight_number;
	vector <Seats> seats;
};

class FlightDao {
public:
	Flight getFlightByTown(string town);
	void addFlight(Flight flight);
	void deletFlight(Flight flight);
};

