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
	vector <SharePoint *> sharePoints;
	vector<Client *> clients;


public:
	Company();

	//=========================================================================
	//=================| GET FUNCTIONS |===================================
	//=========================================================================

	vector<SharePoint *> getSharePoints() const;	//vector returned by reference so we can manipulate bikes' vector easily
	vector<Client *> getClients() const;

	//=========================================================================
	//=================| DRIVER MANAGEMENT |===================================
	//=========================================================================
	//Menu for client management
	void clientManagementMenu();
	//Gets information from the user to add a new client
	void addingNewClient();
	//Gets client ID from user and deletes that client
	void removingClient();
	//Gets new pair of coordinates and updates the location of a given client
	void changeClientLocation();
	//Gets information to set a bike to a user and delete it from the sharepoint it was in
	void pickBike();
	//Gets id from the client/user to return the bike to the sharepoint where he is standing
	void returnBike();



	//=========================================================================
	//================| SHARE POINT MANAGEMENT |===============================
	//=========================================================================
	//Menu for share point management
	void sharePointManagementMenu();
	//Gets information from the user to create a new share point
	void addingNewSharePoint();
	//Removes a share point with the coordinates pointed by user
	void removingSharePoint();
	//Gets information about which type of bike to add to which sharepoint (already has to exist)
	 void addingBikeToSharePoint();

	 //=========================================================================
	 //========================| SEARCH |=======================================
	 //=========================================================================

	 //if there is a SharePoint at (x,y), returns its index, otherwise returns -1
	 int findSharePoint(int x, int y) const;
	 //if there is a Client with clientID, returns its index, otherwise returns -1
	 int findClient(unsigned int clientID) const;

	 //=========================================================================
	 //===================| VECTORS MANAGEMENT |===============================
	 //=========================================================================

	//add new SharePoint (pointer) to vector sharePointers
	void addSharePoint(SharePoint * p1);
	//remove SharePoint (pointer) at location (x,y)
	void removeSharePoint(int x, int y);
	//add new client (pointer) to vector clients
	void addClient(Client * c1);
	//remove client with id clientID
	void removeClient(unsigned int clientID);
	//add bike (pointer) of type bikeType to SharePoint at location (x,y)
	void addBike(int x, int y, string bikeType);


	//=========================================================================
	//==================| PICK/RETURN BIKES AND PAYMENTS |=====================
	//=========================================================================

	//if Client with clientID has no current bike, it peeks a bikeType bike from closest SharePoint
	void clientPickBike(unsigned int clientID, string bikeType);
	//if Client with clientID has current bike, returns bike at closest not full SharePoint and pays/accumulate amount too pay
	void clientReturnBike(unsigned int clientID);
	//end of month (partners pay)
	void endOfMonth();

	//=========================================================================
	//======================| FILES MANAGEMENT |===============================
	//=========================================================================

	//save SharePoints' information in a file connected to ostream outFile
	void saveSharePoints(ostream & outFile);
	//save clients' information in a file connected to ostream outFile
	void saveClients(ostream & outFile);
	//converts a string from a file of sharePoints to an object of type SharePoint and returns a pointer to it
	SharePoint * stringToSharePoint(string p1);
	//converts a string from a file of clients to a object of type Client and returns a pointer to it
	Client * stringToClient(string c1);
	//returns a pointer to a bike of type b1
	Bike * stringToBike(string b1);
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
	int x, y;

public:
	ExistentSharePoint(int x, int y) {this->x = x; this->y = y;}
	string getInformation() {return ("( " + to_string(x) + " , " + to_string(y) + ") ");}
};


//there isn't a SharePoint at coordinates (x,y) to remove
class NotExistentSharePoint
{
private:
	int x, y;

public:
	NotExistentSharePoint(int x, int y) {this->x = x; this->y = y;}
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


//if we try to add a bike to a Full SharePoint
class FullSharePoint
{
private:
	int x, y;

public:
	FullSharePoint(int x, int y) {this->x = x; this->y = y;}
	int getX() {return x;}
	int getY() {return y;}

};


class NotExistentBikeType
{
private:
	string type;

public:
	NotExistentBikeType(string type) {this->type = type;}
	string getType() {return type;}

};

class ClientAlreadyWithBike
{
public:
	ClientAlreadyWithBike() {}
};

class ClientWithoutBike
{
public:
	ClientWithoutBike() {}
};

#endif
