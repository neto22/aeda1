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

	//virtual void pay(unsigned int hours);


};

//=================================================================
//Partner//========================================================
//=================================================================
class Partner: public Client
{
protected:
	unsigned int monthPayment;		//amount that partner pays monthly to get discounts
	unsigned int bikesPayment = 0;	//amount to pay for bikes rented along month
	unsigned int hoursMonth = 0;	//hours of rent

public:
	Partner(string nome, double x, double y);
	string getInformation() const;
	string getType() const;
	//acumulate bike payment to bikesPayment and hoursMonth
	//void pay(unsigned int hours);
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
	//print value that regular pays ( bike->pricePerHour * hours)
	//void pay(unsigned int hours);
};


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
