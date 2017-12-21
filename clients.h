#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "bike.h"
#include "global.h"
#include "sharePoint.h"


//=================================================================
//Client//=========================================================
//=================================================================

/**
 * @brief Client cladss: has a user ID, name, current position (x and y coordinates) and bike they are using. There are two types of Clients (Partner and Regular), implemented as derived classes.
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
	 * @brief Sets Client's ID
	 * @param user_id User ID
	 * @return void
	 */
	void setID(unsigned int user_id);	//usefull to get clients correctly from file
	/**
	 * @brief Sets Client's x-coordinate
	 * @param x x-coordinate
	 * @return void
	 */
	void setX(int x);
	/**
	 * @brief Sets Client's y-coordinate
	 * @param y y-coordinate
	 * @return void
	 */
	void setY(int y);
	/**
	 * @brief Sets Client's current bike
	 * @param b1 Bike (pointer) to rent
	 * @return void
	 */
	void setCurrentBike(Bike * b1);

	//distance to SharePoint

	/**
	 * @brief Calculates the distance between the Client and a SharePoint
	 * @param p1 SharePoint you want to know the distance to
	 * @return distance to SharePoint
	 */
	double distance(SharePoint p1);
	/**
	 * @brief Finds closest SharePoint (pointer) to Client pick a Bike of type bikeType
	 * @param sharePoints SharePoints' vector
	 * @param bikeType type of bike you want to rent
	 * @return closest SharePoint (pointer) with bike of the type requested (if there is an avaible SharePoint)
	 */
	SharePoint * closestSHtoPick(const vector<SharePoint *> & sharePoints, string bikeType);

	/**
	 * @brief Finds closest not full SharePoint (pointer) to Client
	 * @param sharePoints SharePoints (pointers) vector
	 * @return closest not full SharePoint (pointer), if there is one
	 */
	SharePoint * closestSHtoReturn(const vector<SharePoint *> & sharePoints);

	//payment functions

	/**
	 * @brief virtual pay function
	 * @param hours Number of hours Bike was rented
	 * @return void
	 */
	virtual void pay(unsigned int hours);
	/**
	 * @brief virtual pay function at the end of the month (for Partner class only)
	 * @return void
	 */
	virtual void payMonth();	//only relevant to partner


};

//=================================================================
//Partner//========================================================
//=================================================================

/**
 * @brief Partner is a Client sub-class which makes the payments at the end of the month with a 5% discount or 10% discount (if total hours above 20), the discount is applied at bikesPayment (excluding monthPayment)
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
	 * @return string with Client's information in the format "Partner ; user_id ; name ; ( x , y ) ; Current Bike"
	 */
	string getInformation() const;
	/**
	 * @return type : "Partner"
	 */
	string getType() const;
	/**
	 * @brief Accumulate bike payment to bikesPayment and hours rented to hoursMonth
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
	/**
	 * @return string with Client's information in the format "Regular ; user_id ; name ; ( x , y ) ; Current Bike"
	 */
	string getInformation() const;
	/**
	 * @return type : "Regular"
	 */
	string getType() const;
	/**
	 * @brief Client pays automatically when returning Bike (print value that Regular pays: bike->pricePerHour * hours)
	 * @param hours hours Bike was used
	 * @return void
	 */
	void pay(unsigned int hours);
};


//=================================================================
//Exeptions//======================================================
//=================================================================

/**
 * @brief There are no available points to return bike (all SharePoints are full) or to pick bike (no SharePoint has bikeType)
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
	 * @param bikeType Type of Bike trying to be picked
	 */
	NotAvaibleSharePoints(string bikeType) {this->bikeType = bikeType;}
	/**
	 * @return Type of Bike trying to be picked
	 */
	string getBykeType() const {return bikeType;}
};

#endif
