#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "bike.h"
#include "global.h"
#include "sharePoint.h"


//=================================================================
//Client//=========================================================
//=================================================================

/**
 * @brief Client class: has a user ID, name, current position (x and y coordinates) and bike they are using. There are two types of Clients (Partner and Regulars) and so the Clients class is abstract.
 */
class Client
{
protected:
	unsigned int user_id;
	string name;
	int x;
	int y;
	Bike * currentBike = NULL;

public:
	/**
	 * @brief Client constructor
	 * @param name client's name
	 * @param x x-coordinate
	 * @param y y-coordinate
	 */
	Client(string name,int x, int y);
	static unsigned int id_counter;

	//get functions

	/**
	 * @return Client's ID
	 */
	unsigned int getID() const;
	/**
	 * @return Client's name
	 */
	string getName() const;
	/**
	 * @return Client's x-coordinate
	 */
	int getX() const;
	/**
	 * @return Client's y-coordinate
	 */
	int getY() const;
	/**
	 * @return Client's type
	 */
	virtual string getType() const;
	/**
	 * @return Client's information
	 */
	virtual string getInformation() const;
	/**
	 * @return Client's current bike
	 */
	Bike * getCurrentBike() const;

	//set functions

	/**
	 * @brief Sets client's ID
	 * @param user_id User ID
	 * @return void
	 */
	void setID(unsigned int user_id);	//usefull to get clients correctly from file
	/**
	 * @brief Sets client's x-coordinate
	 * @param x x-coordinate
	 * @return void
	 */
	void setX(int x);
	/**
	 * @brief Sets client's y-coordinate
	 * @param y y-coordinate
	 * @return void
	 */
	void setY(int y);
	/**
	 * @brief Sets client's current bike
	 * @param b1 bike to rent
	 * @return void
	 */
	void setCurrentBike(Bike * b1);

	//distance to SharePoint

	/**
	 * @brief Calculates the distance between the client and a SharePoint
	 * @param SharePoint SharePoint you want to know the distance to
	 * @return distance to SharePoint
	 */
	double distance(SharePoint p1);
	/**
	 * @brief Finds closest SharePoint (pointer) to Client to pick a bike of type bikeType
	 * @param sharePoints SharePoints vector
	 * @param bikeType type of bike you want to rent
	 * @return closest SharePoint with bike of the type requested available
	 */
	SharePoint * closestSHtoPick(const vector<SharePoint *> & sharePoints, string bikeType);

	/**
	 * @brief Finds closest not full SharePoint (pointer) to Client
	 * @param sharePoints SharePoints vector
	 * @return closest SharePoint with not full
	 */
	SharePoint * closestSHtoReturn(const vector<SharePoint *> & sharePoints);

	//payment functions

	/**
	 * @brief virtual pay function
	 * @param hours Number of hours rented
	 * @return void
	 */
	virtual void pay(unsigned int hours);
	/**
	 * @brief virtual pay function at the end of the month (for partners only)
	 * @return void
	 */
	virtual void payMonth();	//only relevant to partner


};

//=================================================================
//Partner//========================================================
//=================================================================

/**
 * @brief Partner is a Client sub-class which makes the payments at the end of the month with a 5% discount or 10% discount (if total hours above 20)
 */
class Partner: public Client
{
protected:
	unsigned int monthPayment;		//amount that partner pays monthly to get discounts
	unsigned int bikesPayment = 0;	//amount to pay for bikes rented along month
	unsigned int hoursMonth = 0;	//hours of rent

public:
	/**
	 * @brief Partner constructor, starts with base payment 10/month
	 * @param name Client's name
	 * @param x Client's x-position
	 * @param y Client's y-position
	 */
	Partner(string name, int x, int y);

	/**
	 * @return string with Client's information in the format "Partner ; user_id ; name ; ( x , y ) ; "
	 */
	string getInformation() const;
	/**
	 * @return Partner
	 */
	string getType() const;
	/**
	 * @brief Accumulate bike payment to bikesPayment and hoursMonth
	 * @param hours hours used
	 * @return void
	 */
	void pay(unsigned int hours);
	/**
	 * @brief Client pays end of the month (apply discounts and reset bikesPayment and hoursMonth)
	 * @return void
	 */
	void payMonth();
};

//=================================================================
//Regular//========================================================
//=================================================================

/**
 * @brief Regular is a Client sub-class which makes the payments when returning bike
 */
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

/**
 * @brief There are no available points to return bike (all SharePoints are full)
 */
class NotAvaibleSharePoints
{
protected:
	string bikeType = "";
public:
	/**
	 * @brief NotAvaibleSharePoints constructor
	 */
	NotAvaibleSharePoints() {}
	/**
	 * @brief NotAvaibleSharePoints constructor
	 * @param bikeType Type of bike trying to be returned
	 */
	NotAvaibleSharePoints(string bikeType) {this->bikeType = bikeType;}
	/**
	 * @return Type of bike trying to be returned
	 */
	string getBykeType() const {return bikeType;}
};

#endif
