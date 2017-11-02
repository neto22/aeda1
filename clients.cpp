#include "clients.h"	/*only enough to work at SharePoint and Company*/

//static

unsigned int Client::id_counter = 1;

//constructors
Client::Client(string name, double x, double y)	: user_id(id_counter)
{
	this->name = name;
	this->x = x;
	this->y = y;

	id_counter++;
}

Partner::Partner(string name, double x, double y) : Client(name, x, y)
{
	Client::setType(1);
}

Regular::Regular(string name, double x, double y) : Client(name, x, y)
{
	Client::setType(2);
}

//get functions

unsigned int Client::getID() const
{
	return user_id;
}

string Client::getName() const
{
	return name;
}

double Client::getX() const
{
	return x;
}


double Client::getY() const
{
	return y;
}

int Client::getType() const
{
	return type;
}

//set functions

void Client::setX(double x)
{
	this->x = x;
}

void Client::setY(double y)
{
	this->y = y;
}

void Client::setType(int type)
{
	this->type = type;
}

//operator

ostream & operator << (ostream & os, Client c1)
{
	if(c1.getType() == 1)
		os << "Partner";
	else
		os << "Regular";

	os << " ; " << to_string(c1.getID()) << " ; " << c1.getName() << " ; ( " << to_string(c1.getX()) << " , " << to_string(c1.getY()) << " )";

	return os;
}
