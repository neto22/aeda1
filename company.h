#ifndef COMPANY_H
#define COMPANY_H

#include "sharePoint.h"
#include "clients.h"
#include <sstream>

//=================================================================
//Company//========================================================
//=================================================================
class Company
{
private:
	vector <SharePoint> sharePoints;
	vector<Client *> clients;


public:
	Company();

	//get functions

	vector<SharePoint> getSharePoints() const;	//vector returned by reference so we can manipulate bikes' vector easily
	vector<Client *> getClients() const;

	//vectors management

	//add new SharePoint (pointer) to vector sharePointers
	void addSharePoint(SharePoint p1);
	//remove SharePoint (pointer) at location (x,y)
	void removeSharePoint(double x, double y);
	//add new client (pointer) to vector clients
	void addClient(Client * c1);
	//remove client with id clientID
	void removeClient(unsigned int clientID);
	//add bike (pointer) b1 to SharePoint with index sharePointIndex
	void addBike(Bike * b1, unsigned int sharePointIndex);


	//file's management

	//save SharePoints' information in a file connected to ostream outFile
	void saveSharePoints(ostream & outFile);
	//save clients' information in a file connected to ostream outFile
	void saveClients(ostream & outFile);
	//converts a string from a file of sharePoints to an object of type SharePoint and returns a pointer to it
	SharePoint stringToSharePoint(string p1);
	//converts a string from a file of clients to a object of type Client and returns a pointer to it
	Client * stringToClient(string c1);
	//read SharePoints from file connected to istream inFile and save them at sharePoints vector
	void readSharePoints(istream & inFile);
	//read Clients from file connected to istream inFile and save them at clients vector
	void readClients(istream & inFile);

};


//=================================================================
//Exeptions//======================================================
//=================================================================

//location (x,y) already as a SharePoint (we can´t add another with this coordinates)
class ExistentSharePoint
{
private:
	double x, y;

public:
	ExistentSharePoint(double x, double y) {this->x = x; this->y = y;}
	string getInformation() {return ("( " + to_string(x) + " , " + to_string(y) + ") ");}
};

//there isn't a SharePoint at coordinates (x,y) to remove
class NotExistentSharePoint
{
private:
	double x, y;

public:
	NotExistentSharePoint(double x, double y) {this->x = x; this->y = y;}
	string getInformation() {return ("( " + to_string(x) + " , " + to_string(y) + ") ");}
};

//there isn't a client with id user_id to remove
class NotExistentClient
{
private:
	unsigned int user_id;

public:
	NotExistentClient(unsigned int user_id) {this->user_id = user_id;}
	unsigned int getID() {return user_id;}

};


#endif
