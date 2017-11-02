#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "ap.h"
#include "bike.h"

class Client
{
protected:
	unsigned int user_id;
	string name;
	double x;
	double y;
	static unsigned int id_counter;
	int type;	//Partner = 1; Regular = 2
	Bike currentBike;

public:
	Client(string nome, double x, double y);

	//virtual double pay();

	//get functions

	unsigned int getID() const;
	string getName() const;
	double getX() const;
	double getY() const;
	int getType() const;

	//set functions

	void setX(double x);
	void setY(double y);
	void setType(int type);

};

//other operator, that automatically turns a Client into a string
ostream & operator << (ostream & os, Client c1);
class Partner: public Client
{
public:
	Partner(string nome, double x, double y);
	//double pay();
};

class Regular: public Client
{
public:
	Regular(string nome, double x, double y);
	//double pay();
};


#endif
