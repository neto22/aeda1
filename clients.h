#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "ap.h"
#include "bike.h"
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
	int type;	//Partner = 1; Regular = 2
	Bike * currentBike = NULL;

public:
	Client(string nome, double x, double y);
	static unsigned int id_counter;

	//get functions

	unsigned int getID() const;
	string getName() const;
	double getX() const;
	double getY() const;
	int getType() const;

	//set functions

	void setID(unsigned int user_id);	//usefull to get clients correctly from file
	void setX(double x);
	void setY(double y);
	void setType(int type);

	//other functions

	//calculates the distance between the client and a SharePoint (given as argument)
	double distance(SharePoint p1);
	//returns closest SharePoint to Client to peek a bike of type bikeType
	SharePoint closestSHtoPeek(const vector<SharePoint> & sharePoints, string bikeType);
	//returns closest not full SharePoint to Client
	SharePoint closestSHtoReturn(const vector<SharePoint> & sharePoints);
	//virtual double pay();


};

//=================================================================
//Partner//========================================================
//=================================================================
class Partner: public Client
{
public:
	Partner(string nome, double x, double y);
	//double pay();
};

//=================================================================
//Partner//========================================================
//=================================================================
class Regular: public Client
{
public:
	Regular(string nome, double x, double y);
	//double pay();
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
