#ifndef COMPANY_H
#define COMPANY_H

#include "sharePoint.h"
#include "clients.h"
#include "workshop.h"
#include "store.h"
#include "junkyard.h"

#include <sstream>
#include <queue>

//=================================================================
//Company//========================================================
//=================================================================

/**
 * @brief Company class: a class to save Clients and SharePoints (all pointers)
 */
class Company
{
	friend class Workshop;
	friend class Junkyard;

private:
	vector <SharePoint *> sharePoints;
	vector<Client *> clients;
	priority_queue<Store> stores;


public:
	/**
	 * @brief Company constructor, just creates a company so we can save the Clients and the SharePoints
	 */
	Company();


//=========================================================================
//==================| STARTS 1� PART |=====================================
//=========================================================================


	//=========================================================================
	//=================| GET FUNCTIONS |===================================
	//=========================================================================

	/**
	 * @return vector of all SharePoints (pointers)
	 */
	vector<SharePoint *> getSharePoints() const;	//vector returned by reference so we can manipulate bikes' vector easily
	/**
	 * @return vector of all Clients (pointers)
	 */
	vector<Client *> getClients() const;
	/**
	 * @return priority_queue with all stores
	 */
	priority_queue<Store> getStores() const;

	//=========================================================================
	//=================| DRIVER MANAGEMENT |===================================
	//=========================================================================

	/**
	 * @brief Menu for Clients' Management
	 * @return void
	 */
	void clientManagementMenu();
	/**
	 * @brief Gets information from the user to add a new Client
	 * @return void
	 */
	void tryAddNewClient();
	/**
	 * @brief Gets information from the user to add a new Client
	 * @return void
	 */
	//Gets client ID from user and deletes that Client
	void tryRemoveClient();
	/**
	 * @brief Gets new pair of coordinates and updates the location of a given Client
	 * @return void
	 */
	void tryChangeClientLocation();
	/**
	 * @brief Gets information to set a Bike to a user and delete it from the closest SharePoint it was in
	 * @return void
	 */
	void tryPickBike();
	/**
	 * @brief Gets id from the Client/user to return the Bike to the closest SharePoint where he is standing
	 * @return void
	 */
	void tryReturnBike();



	//=========================================================================
	//================| SHARE POINT MANAGEMENT |===============================
	//=========================================================================

	/**
	 * @brief Menu for SharePoints' Management
	 * @return void
	 */
	void sharePointManagementMenu();
	/**
	 * @brief Gets information from the user to create a new SharePoint
	 * @return void
	 */
	void tryAddNewSharePoint();
	/**
	 * @brief Removes a SharePoint with the name given by user
	 * @return void
	 */
	void tryRemoveSharePoint();
	/**
	 * @brief Gets information about which type of bike to add to which SharePoint (already has to exist)
	 * @return void
	 */
	 void tryAddBikeToSharePoint();
	 /**
	  * @brief Gets information about which type of Bike to remove from SharePoint (already has to exist)
	  * @return void
	  */
	 void tryRemoveBikeFromSharePoint();

	 //=========================================================================
	 //================| SHARE POINT ANALYSIS |===============================
	 //=========================================================================

	 /**
	  * @brief Menu for SharePoints' Analysis
	  * @return void
	  */
	 void sharePointAnalysisMenu();

	 /**
	  * @brief prints the number of Bikes available in all SharePoints by type
	  * @return void
	  */
	 void printAllBikesAvailable();

	 /**
	  *@brief prints the information of a SharePoint ordered by the total number of Bikes
	  *@return void
	  */
	 void printOrderedByTotalBikes();

	 /**
	  * @brief prints the information of a SharePoint ordered by its occupancy
	  * @return void
	  */
	 void printOrderedByOccupancy();

	 /**
	  * @brief prints the average number of Bikes per SharePoint, the lowest amount, the highest, and the standart deviaton
	  * @return void
	  */
	 void statisticAnalysis();

	 /**
	  * @brief redistributes the bikes from all SharePoints so they are more balanced in quantity and type
	  * 1 step: makes a vector with all the Bikes
	  * 2 step: makes an ordered vector with all the Bikes (by type)
	  * 3 step: loop throught all the sharepoints and give a bike (therefore the quantity and type will be as well distributed as possible
	  * @return void
	  */
	 void redistributeBikes();

	 /**
	  * @brief displays the Bikes by type by SharePoint to auxiliate decision of redistribution
	  * @return void
	  */
	 void displayBikesBySharePoint();

	 //=========================================================================
	 //========================| SEARCH |=======================================
	 //=========================================================================


	 /**
	  * @brief Gets SharePoint's index
	  * @return its index if there is a SharePoint at (x,y)
	  * @return -1 otherwise
	  */
	 int findSharePoint(int x, int y) const;
	 /**
	  * @brief Gets SharePoint's index (overloading of function findSharePoint)
	  * @return its index if there is a SharePoint with this name
	  *  @return -1 otherwise
	  */
	 int findSharePoint(string name) const;
	 /**
	  * @brief Gets Client's index
	  * @return its index if there is a Client with clientID
	  * @return -1 otherwise
	  */
	 int findClient(unsigned int clientID) const;

	 //=========================================================================
	 //===================| VECTORS MANAGEMENT |===============================
	 //=========================================================================


	 /**
	 * @brief Add new SharePoint (pointer) to vector sharePointers
	 * @param p1 SharePoint (pointer) you want to add
	 * @return void
	 */
	void addSharePoint(SharePoint * p1);
	/**
	 * @brief Remove SharePoint (pointer) with name we insert (Overload of removeSharePoint function)
	 * @param name SharePoint's name
	 * @return void
	 */
	void removeSharePoint(string name);
	 /**
	 * @brief Add new Client (pointer) to vector clients
	 * @param c1 Client (pointer) you want to add
	 * @return void
	 */
	void addClient(Client * c1);
	 /**
	 * @brief Remove client with id clientID
	 * @param clientID ID of the Client we want to remove
	 * @return void
	 */
	void removeClient(unsigned int clientID);
	/**
	 * @brief Move Client with id clientID to location (x,y)
	 * @param clientID ID of the client
	 * @param x - new x-coordinate
	 * @param y - new y-coordinate
	 * @return void
	 */
	void changeClientLocation(unsigned int clientID, int x, int y);
	 /**
	 * @brief Add Bike (pointer) of type bikeType to SharePoint with name nameSharePoint
	 * @param nameSharePoint SharePoint's name
	 * @param bikeType type of the bike
	 * @return void
	 */
	void addBike(string nameSharePoint, string bikeType);
	/**
	 * @brief Remove bike (pointer) of type bikeType from SharePoint with name nameSharePoint
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @param bikeType type of the bike
	 * @return void
	 */
	void removeBike(string nameSharePoint, string bikeType);
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
	 * @brief if Client with clientID has no current bike, it picks a bikeType Bike from closest SharePoint
	 * @param clientID ID of the client
	 * @param bikeType type of Bike
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
	 * @brief End of month (clients of type Partner pay)
	 * @return void
	 */
	void endOfMonth();




//=========================================================================
//==================| STARTS 2� PART |=====================================
//=========================================================================

	//=========================================================================
	//==================| SHOPS MANAGEMENT |===================================
	//=========================================================================

	/**
	 * @brief Receives a name and searches a Store named with it
	 * @returns Returns true if there is a Store with the name given and false otherwise
	 */
	bool findStore(string name);

	/**
	 * @brief Receives the needed arguments to create a Store (name  and number of bikes of each type), creates it and add it to the priority_queue
	 *
	 * @param name String with name of the Store
	 * @param numUrban Integer with number of Urban bikes the Store will have
	 * @param numSimpleUrban Integer with number of SimpleUrban bikes the Store will have
	 * @param numChild Integer with number of Child bikes the Store will have
	 */
	void addStore(string name, int numUrban, int numSimpleUrban, int numRace, int numChild);	//MAYBE ADD EXEPTIONS

	/**
	 * @brief Removes Store with given name from priority_queue stores
	 * @param name String with the name of the store to remove
	 */
	void removeStore(string name);	//MAYBE ADD EXEPTIONS

	/**
	 * @brief Searches best store with enough stock of bikes (numBikes of type bikeType) take it (removing it) from the stores priority_queue
	 *  and returning it
	 *
	 * @param bikeType type of bikes wich stock we want to check
	 * @param numBikes number of bikes
	 * @return Returns best store with stock enough
	 */
	Store popAvailableShop(string bikeType, int numBikes);

	/**
	 * @brief Prints informarion of all stores
	 */
	void showAllStores();

	/**
	 * @brief Prints information of top 5 best stores (5 stores with best reputation)
	 */
	void showTopStores();


	//=========================================================================
	//==================| SHOPS MENU/FUNCIONALITIES|===========================
	//=========================================================================

	/**
	 * @brief Menu for Clients' Management
	 * @return void
	 */
	void storeManagementMenu();

	/**
	 * @brief Takes information from user of the Store atributes as name and number of bikes of each type
	 *  to create and add a Store to the priority_queue
	 *  If there already is a Store with given name the addStore function throws an exception
	 */
	void userAddStore();

	/**
	 * @brief Takes information from user of the name of the Store to remove
	 *  If there is Store with given name it is removed, otherwise an exception is thrown by the remove function
	 */
	void userRemoveStore();

	/**
	 * @brief Takes information from user of the number and tipe of bikes to purchase and sells the bikes wished from the best store with stock
	 * If there isn't  store with enough stock an exception is thrown
	 */
	void userPurchasesBikes();

	//=========================================================================
	//==================| JUNKYADR AUXILIAR FUNCTION|==========================
	//=========================================================================

	/**
	 * @brief Takes information of SharePoint where the broken/damaged bike is and its type and send it to the Junkyard j1
	 * @param j1 Junkyard to where broken bike is sent to wait to be wrecked/demolished
	 */
	void sendBikeToJunkyard(Junkyard & j1);



//=========================================================================
//==================| FOR BOTH PARTS |=====================================
//=========================================================================

	//=========================================================================
	//======================| FILES |==========================================
	//=========================================================================

	/**
	 * @brief Save SharePoint's information in a file connected to ostream outFile
	 * @param outFile
	 * @return void
	 */
	void saveSharePoints(ostream & outFile);
	/**
	 * @brief Save client's information in a file connected to ostream outFile
	 * @param outFile
	 * @return void
	 */
	void saveClients(ostream & outFile);
	/**
	 * @brief Converts a string from a file of a SharePoints to an object of type SharePoint
	 * @param p1 string with SharePoint's information
	 * @return pointer to SharePoint converted from string p1
	 */
	SharePoint * stringToSharePoint(string p1);
	/**
	 * @brief Converts a string from a file of Clients to an object of type Client
	 * @param c1 string with Client's information
	 * @return pointer to Client converted from string c1
	 */
	Client * stringToClient(string c1);
	/**
	 * @brief Converts a string of a Bike to an objct of type Bike
	 * @return pointer to a Bike converted from string b1
	 */
	Bike * stringToBike(string b1);
	/**
	 * @brief Read SharePoints from file connected to istream inFile and save them at sharePoints vector
	 * @param inFile
	 * @return void
	 */
	void readSharePoints(istream & inFile);
	/**
	 * @brief Read Clients from file connected to istream inFile and save them at clients vector
	 * @param inFile
	 * @return void
	 */
	void readClients(istream & inFile);


	/**
	 * @brief Save Stores' information in a file connected to ostream outFile
	 * @param outFile
	 * @return void
	 */
	void saveStores(ostream & outFile);

	/**
	 * @brief Converts a string of a Store to an object of type Store
	 * @param s1 String with Store's information we want to an object of type Store
	 * @return Store converted from string s1
	 */
	Store stringToStore(string s1);

	/**
	 * @brief Read Stores from file connected to istream inFile and save them at stores vector
	 * @param inFile
	 * @return void
	 */
	void readStores(istream & inFile);

};


//=================================================================
//Exeptions//======================================================
//=================================================================

/**
 * @brief Location (x,y) already as a SharePoint (we can't add another with this coordinates)
 */
class AlreadyExistentSharePointAtLocation
{
private:
	int x, y;

public:
	/**
	 * @brief Already Existent SharePoint at Location Constructor
	 */
	AlreadyExistentSharePointAtLocation(int x, int y) {this->x = x; this->y = y;}
	/**
	 * @return String with coordinates trying to be repeated in the format "( x , y ) "
	 */
	string getInformation() {return ("Already exists a SharePoint at location : (" + to_string(x) + " , " + to_string(y) + ") ");}
};


/**
 * @brief Already has a SharePoint with name specified (we can't add another with this name)
 */
class AlreadyExistentSharePointWithName
{
private:
	string name;

public:
	/**
	 * @brief Already Existent SharePoint With Name Constructor
	 */
	AlreadyExistentSharePointWithName(string name) {this->name = name;}
	/**
	 * @return String with coordinates trying to be repeated in the format "( x , y ) "
	 */
	string getInformation() {return ("Already exists a SharePoint with name : " + name);}

};


/**
 * @brief There isn't a SharePoint with name sharePointName to remove
 */
class NotExistentSharePoint
{
private:
	string sharePointName;

public:
	/**
	 * @brief Non-Existent SharePoint Constructor
	 */
	NotExistentSharePoint(string sharePointName) {this->sharePointName = sharePointName;}

	/**
	 * @return String with name not found : sharePointName
	 */
	string getName() {return sharePointName;}

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
	string nameSharePoint;

public:
	/**
	 * @brief FullSharePoint constructor
	 * @param nameSharePoint name of full SharePoint
	 */
	FullSharePoint(string nameSharePoint) {this->nameSharePoint = nameSharePoint;}
	/**
	 * @return FullSharePoint's name
	 */
	string getName() {return nameSharePoint;}


};


/**
 * @brief Non-Existent Bike's type at SharePoint
 */
class NotExistentBikeType
{
private:
	string type;

public:
	/**
	 * @brief Non-Existent bike type at SharePoint
	 * @param type non-existing type at SharePoint
	 */
	NotExistentBikeType(string type) {this->type = type;}
	/**
	 * @return non-existing type as string
	 */
	string getType() {return type;}

};


/**
 * @brief Client is still with a Bike, he must return it before pick another
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
 * @brief Client doesn't have a Bike at the moment to return
 */
class ClientWithoutBike
{
public:
	/**
	 * @brief ClientWithoutBike constructor
	 */
	ClientWithoutBike() {}
};


/**
 * @brief There isn't any Store with enough stock  to satisfy user's request
 */
class NotAvailableStores
{
private:
	string bikeType;
	int numBikes;

public:
	/**
	 * @brief ClientWithoutBike constructor
	 */
	NotAvailableStores(string bikeType, int numBikes) {this->bikeType = bikeType; this->numBikes = numBikes;}
	string getBikeType() const {return bikeType;}
	int getNumBikes() const {return numBikes;}
};

/**
 * @brief There is already a Store with name give so we can add it to the priority_queue
 */
class AlreadyExistentStore
{
private:
	string name;

public:
	/**
	 * @brief AlreadyExistentStore constructor
	 */
	AlreadyExistentStore(string name) {this->name = name;}
	string getName() const {return name;}
};

/**
 * @brief There isn't a Store with given name so we can't remove it from the priority_queue
 */
class NotExistentStore
{
private:
	string name;

public:
	/**
	 * @brief NotExistentStore
	 */
	NotExistentStore(string name) {this->name = name;}
	string getName() const {return name;}
};

#endif
