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
	int x;
	int y;
	Bike * currentBike = NULL;

public:
	Client(string name,int x, int y);
	static unsigned int id_counter;

	//get functions

	unsigned int getID() const;
	string getName() const;
	int getX() const;
	int getY() const;
	virtual string getType() const;
	virtual string getInformation() const;
	Bike * getCurrentBike() const;

	//set functions

	void setID(unsigned int user_id);	//usefull to get clients correctly from file
	void setX(int x);
	void setY(int y);
	void setCurrentBike(Bike * b1);

	//distance to SharePoint

	//calculates the distance between the client and a SharePoint (given as argument)
	double distance(SharePoint p1);
	//returns closest SharePoint (pointer) to Client to pick a bike of type bikeType
	SharePoint * closestSHtoPick(const vector<SharePoint *> & sharePoints, string bikeType);
	//returns closest not full SharePoint (pointer) to Client
	SharePoint * closestSHtoReturn(const vector<SharePoint *> & sharePoints);

	//payment functions

	virtual void pay(unsigned int hours);
	virtual void payMonth();	//only relevant to partner


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
	Partner(string name, int x, int y);
	string getInformation() const;
	string getType() const;
	//accumulate bike payment to bikesPayment and hoursMonth
	void pay(unsigned int hours);
	//client pays end of the month (apply discounts and reset bikesPayment and hoursMonth
	void payMonth();
};

//=================================================================
//Regular//========================================================
//=================================================================
class Regular: public Client
{
public:
	Regular(string name, int x, int y);
	string getInformation() const;
	string getType() const;
	//print value that regular pays ( bike->pricePerHour * hours)
	void pay(unsigned int hours);
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
