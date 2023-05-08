#include <string>
#include <iostream>
#include "Flight.h"

using namespace std;
#pragma once
class Ticket
{
public:
	User user;
	Flight flight;
};

class TicketDao {
public:
	Ticket getTicketByUser(User user);
	void addTicket(User user, Flight flight);
	void deleteTicket(User user);
};

