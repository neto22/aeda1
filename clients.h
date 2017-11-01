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
	Bike currentBike;

public:
	Client(string nome, double x, double y);
	//virtual double pay();
	unsigned int getID() const;
	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);

};

class Partner: public Client
{
public:
	//double pay();
};

class Regular: public Client
{
public:
	//double pay();
};


#endif
