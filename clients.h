#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "bike.h"
#include "global.h"
#include "sharePoint.h"


//=================================================================
//Client//=========================================================
//=================================================================
class Client
{
protected:
	unsigned int user_id;
	string name;
	double x;
	double y;
	Bike * currentBike = NULL;

public:
	Client(string nome, double x, double y);
	static unsigned int id_counter;

	//get functions

	unsigned int getID() const;
	string getName() const;
	double getX() const;
	double getY() const;
	virtual string getType() const;
	virtual string getInformation() const;
	Bike * getCurrentBike() const;

	//set functions

	void setID(unsigned int user_id);	//usefull to get clients correctly from file
	void setX(double x);
	void setY(double y);
	void setCurrentBike(Bike * b1);

	//distance to SharePoint

	//calculates the distance between the client and a SharePoint (given as argument)
	double distance(SharePoint p1);
	//returns closest SharePoint (pointer) to Client to peek a bike of type bikeType
	SharePoint * closestSHtoPick(const vector<SharePoint *> & sharePoints, string bikeType);
	//returns closest not full SharePoint (pointer) to Client
	SharePoint * closestSHtoReturn(const vector<SharePoint *> & sharePoints);

	//payment functions

	//virtual unsigned int pay();	//amount to pay for a bike is different (if client is a partner or regular)


};

//=================================================================
//Partner//========================================================
//=================================================================
class Partner: public Client
{
protected:
	unsigned int monthPayment;	//amount that partner pays monthly to get discounts

public:
	Partner(string nome, double x, double y);
	string getInformation() const;
	string getType() const;
	//amount that partner must pay when returns current bike (-5% if hours < 20; -10% if hours >= 20)
	//unsigned int pay(unsigned int hours);
};

//=================================================================
//Partner//========================================================
//=================================================================
class Regular: public Client
{
public:
	Regular(string nome, double x, double y);
	string getInformation() const;
	string getType() const;
	//amount that regular must pay when returns current bike ( bike->pricePerHour * hours , without discount)
	//unsigned int pay(unsigned int hours);
};


//operator that automatically turns a Client into a string
ostream & operator << (ostream & os, Client c1);

//=================================================================
//Exeptions//======================================================
//=================================================================

//there is no avaible points to return bike (all SharePoints are full)
class NotAvaibleSharePoints
{
protected:
	string bikeType = "";
public:
	NotAvaibleSharePoints() {}
	NotAvaibleSharePoints(string bikeType) {this->bikeType = bikeType;}
	string getBykeType() const {return bikeType;}
};

#endif
