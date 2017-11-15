#ifndef COMPANY_H
#define COMPANY_H

#include "sharePoint.h"
#include "clients.h"
#include <sstream>

//=================================================================
//Company//========================================================
//=================================================================

/**
 * @brief Company class: a class to save Clients and SharePoints
 */
class Company
{
private:
	vector <SharePoint *> sharePoints;
	vector<Client *> clients;


public:
	/**
	 * @brief Company constructor, just creates a company so we can save the clients and the sharepoints
	 */
	Company();

	//=========================================================================
	//=================| GET FUNCTIONS |===================================
	//=========================================================================

	/**
	 * @return vector of all SharePoints
	 */
	vector<SharePoint *> getSharePoints() const;	//vector returned by reference so we can manipulate bikes' vector easily
	/**
	 * @return vector of all Clients
	 */
	vector<Client *> getClients() const;

	//=========================================================================
	//=================| DRIVER MANAGEMENT |===================================
	//=========================================================================

	/**
	 * @brief Menu for client management
	 * @return void
	 */
	void clientManagementMenu();
	/**
	 * @brief Gets information from the user to add a new client
	 * @return void
	 */
	void tryAddNewClient();
	/**
	 * @brief Gets information from the user to add a new client
	 * @return void
	 */
	//Gets client ID from user and deletes that client
	void tryRemoveClient();
	/**
	 * @brief Gets new pair of coordinates and updates the location of a given client
	 * @return void
	 */
	void tryChangeClientLocation();
	/**
	 * @brief Gets information to set a bike to a user and delete it from the sharepoint it was in
	 * @return void
	 */
	void tryPickBike();
	/**
	 * @brief Gets id from the client/user to return the bike to the sharepoint where he is standing
	 * @return void
	 */
	void tryReturnBike();



	//=========================================================================
	//================| SHARE POINT MANAGEMENT |===============================
	//=========================================================================

	/**
	 * @brief Menu for share point management
	 * @return void
	 */
	void sharePointManagementMenu();
	/**
	 * @brief Gets information from the user to create a new share point
	 * @return void
	 */
	void tryAddNewSharePoint();
	/**
	 * @brief Removes a share point with the coordinates pointed by user
	 * @return void
	 */
	void tryRemoveSharePoint();
	/**
	 * @brief Gets information about which type of bike to add to which sharepoint (already has to exist)
	 * @return void
	 */
	 void tryAddBikeToSharePoint();

	 //=========================================================================
	 //========================| SEARCH |=======================================
	 //=========================================================================


	 /**
	  * @brief Gets SharePoint index
	  * if there is a SharePoint at (x,y), @return its index else @return -1
	  */
	 int findSharePoint(int x, int y) const;
	 /**
	  * @brief Gets Client index
	  * if there is a Client with clientID, @return its index else @return -1
	  */
	 int findClient(unsigned int clientID) const;

	 //=========================================================================
	 //===================| VECTORS MANAGEMENT |===============================
	 //=========================================================================


	 /**
	 * @brief Add new SharePoint (pointer) to vector sharePointers
	 * @param SharePoint SharePoint you want to add
	 * @return void
	 */
	void addSharePoint(SharePoint * p1);
	 /**
	 * @brief Remove SharePoint (pointer) at location (x,y)
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @return void
	 */
	void removeSharePoint(int x, int y);
	 /**
	 * @brief Add new client (pointer) to vector clients
	 * @param Client Client you want to add
	 * @return void
	 */
	void addClient(Client * c1);
	 /**
	 * @brief Remove client with id clientID
	 * @param clientID ID of the client
	 * @return void
	 */
	void removeClient(unsigned int clientID);
	/**
	 * @brief Change client with id clientID location to (x,y)
	 * @param clientID ID of the client
	 * @param x - new x-coordinate
	 * @param y - new y-coordinate
	 * @return void
	 */
	void changeClientLocation(unsigned int clientID, int x, int y);
	 /**
	 * @brief Add bike (pointer) of type bikeType to SharePoint at location (x,y)
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @param bikeType type of the bike
	 * @return void
	 */
	void addBike(int x, int y, string bikeType);
	/**
	 * @brief show Clients with type clientType from Company
	 * @param clientType type of client
	 * @return void
	 */
	void showClients(string clientType) const;
	/**
	 * @brief show SharePoints from Company
	 * @return void
	 */
	void showSharePoints() const;


	//=========================================================================
	//==================| PICK/RETURN BIKES AND PAYMENTS |=====================
	//=========================================================================

	 /**
	 * @brief if Client with clientID has no current bike, it picks a bikeType bike from closest SharePoint
	 * @param clientID ID of the client
	 * @param bikeType type of bike
	 * @return void
	 */
	void clientPickBike(unsigned int clientID, string bikeType);
	 /**
	 * @brief if Client with clientID has current bike, returns bike at closest not full SharePoint and pays/accumulate amount too pay
	 * @param clientID ID of the client
	 * @return void
	 */
	void clientReturnBike(unsigned int clientID);
	 /**
	 * @brief End of month (partners pay)
	 * @return void
	 */
	void endOfMonth();

	//=========================================================================
	//======================| FILES MANAGEMENT |===============================
	//=========================================================================

	/**
	 * @brief Save SharePoint's information in a file connected to ostream outFile
	 */
	void saveSharePoints(ostream & outFile);
	/**
	 * @brief Save client's information in a file connected to ostream outFile
	 */
	void saveClients(ostream & outFile);
	/**
	 * @brief Converts a string from a file of SharePoint to a object of type SharePoint
	 * @return pointer to SharePoint converted from string
	 */
	SharePoint * stringToSharePoint(string p1);
	/**
	 * @brief Converts a string from a file of clients to a object of type Client
	 * @return pointer to Client converted from string
	 */
	Client * stringToClient(string c1);
	/**
	 * @return pointer to a bike of type b1
	 */
	Bike * stringToBike(string b1);
	/**
	 * @brief Read SharePoints from file connected to istream inFile and save them at sharePoints vector
	 * @return void
	 */
	void readSharePoints(istream & inFile);
	/**
	 * @brief Read Clients from file connected to istream inFile and save them at clients vector
	 * @return void
	 */
	void readClients(istream & inFile);

};


//=================================================================
//Exeptions//======================================================
//=================================================================

/**
 * @brief Location (x,y) already as a SharePoint (we can't add another with this coordinates)
 */
class ExistentSharePoint
{
private:
	int x, y;

public:
	/**
	 * @brief Existent SharePoint Constructor
	 */
	ExistentSharePoint(int x, int y) {this->x = x; this->y = y;}
	/**
	 * @return String with coordinates trying to be repeated in the format "( x , y ) "
	 */
	string getInformation() {return ("( " + to_string(x) + " , " + to_string(y) + ") ");}
};

/**
 * @brief There isn't a SharePoint at coordinates (x,y) to remove
 */
class NotExistentSharePoint
{
private:
	int x, y;

public:
	/**
	 * @brief Non-Existent SharePoint Constructor
	 */
	NotExistentSharePoint(int x, int y) {this->x = x; this->y = y;}
	/**
	 * @return String with coordinates not found in the format "( x , y ) "
	 */
	string getInformation() {return ("( " + to_string(x) + " , " + to_string(y) + ") ");}
};

/**
 * @brief There isn't a client with id user_id to remove
 */
class NotExistentClient
{
private:
	unsigned int user_id;

public:
	/**
	 * @brief Non-Existing Client Constructor
	 */
	NotExistentClient(unsigned int user_id) {this->user_id = user_id;}
	/**
	 * @return ID of the client trying to be removed
	 */
	unsigned int getID() {return user_id;}

};

/**
 * @brief If we try to add a bike to a Full SharePoint
 */
class FullSharePoint
{
private:
	int x, y;

public:
	/**
	 * @brief FullSharePoint constructor
	 * @param x x-coordinate
	 * @param y y-coordinate
	 */
	FullSharePoint(int x, int y) {this->x = x; this->y = y;}
	/**
	 * @return FullSharePoint x-coordinate
	 */
	int getX() {return x;}
	/**
	 * @return FullSharePoint y-coordinate
	 */
	int getY() {return y;}

};

/**
 * @brief Non-Existent bike type
 */
class NotExistentBikeType
{
private:
	string type;

public:
	/**
	 * @brief Non-Existent bike type constructor
	 * @param type non-existing type
	 */
	NotExistentBikeType(string type) {this->type = type;}
	/**
	 * @return non-existing type as string
	 */
	string getType() {return type;}

};

/**
 * @brief Client is still with a bike
 */
class ClientAlreadyWithBike
{
public:
	/**
	 * @brief ClientAlreadyWithBike constructor
	 */
	ClientAlreadyWithBike() {}
};

/**
 * @brief Client doesn't have bike at the moment
 */
class ClientWithoutBike
{
public:
	/**
	 * @brief ClientWithoutBike constructor
	 */
	ClientWithoutBike() {}
};

#endif
