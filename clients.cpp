#include "clients.h"	/*only enough to test some SharePoint functions*/

//constructor
Client::Client(string name, double x, double y)
{
	this->name = name;
	this->x = x;
	this->y = y;
}

//get functions

unsigned int Client::getID() const
{
	return user_id;
}

double Client::getX() const
{
	return x;
}


double Client::getY() const
{
	return y;
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
