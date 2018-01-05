#ifndef SRC_JUNKYARD_H_
#define SRC_JUNKYARD_H_

#include "Bike.h"
#include "Date.h"
#include "display.h"

#include <string>
#include <tr1/unordered_set>


//====================================================================================
//=================| BROKENBIKE |=====================================================
//====================================================================================
/**
 * @brief Class of a Broken Bike: saves the Bike (pointer) to wreck and a Date (to be initialized when it is wrecked)
 */
class BrokenBike
{
private:
	Bike * bike;
	Date date;

public:
	//=========================================================================
	//=================| CONSTRUCTORS |========================================
	//=========================================================================
	/**
	 * @brief Constructor of BrokenBike
	 * @param b1 Pointer to bike we want to send to HashTable
	 */
	BrokenBike(Bike * b1);

	//=========================================================================
	//=================| GET |=================================================
	//=========================================================================
	/**
	 * @brief Returns bike (pointer)
	 * @return Returns Bike's pointer of the broken bike
	 */
	Bike * getBike() const;

	/**
	 * @brief Returns date when it was wrecked
	 * @return Returns date when it was wrecked
	 */
	Date getDate() const;

	//=========================================================================
	//=================| SET |=================================================
	//=========================================================================
	/**
	 * @brief Changes object's date to new date given as argument
	 * @param newDate Date to set at BrokesnBike's date
	 */
	void setDate(Date newDate);

	//=========================================================================
	//=================| BOOLEAN |=============================================
	//=========================================================================
	/**
	 * @brief Checks if bike was already demolished/wrecked (if it was already given an available date)
	 * @return Returns true if it already has the date when it was wrecked, false otherwise
	 */
	bool wrecked() const;

};



//====================================================================================
//=================| JUNKYARD |=======================================================
//====================================================================================
struct Hash
{
	int operator() (BrokenBike b1) const
	{
		return b1.getBike()->getID();
	}

	bool operator() (BrokenBike b1, BrokenBike b2) const
	{
		return b1.getBike()->getID() == b2.getBike()->getID();
	}
};

typedef tr1::unordered_set<BrokenBike, Hash, Hash> HashTable;

class Junkyard
{

private:
	HashTable brokenBikes;
	Date lastDate;	//lastWreck date, when we wreck a car, the date of sucj event must be after this date or equal to this (update this value)
	static unsigned int bikeID; //id to give to bikes sent to the hashtable


public:

	//=========================================================================
	//=================| CONSTRUCTORS |========================================
	//=========================================================================
	/**
	 * @brief Constructor of Junkyard
	 */
	Junkyard();

	//=========================================================================
	//======================| EDIT |===========================================
	//=========================================================================
	/**
	 * @brief add bike given as an argument to the HashTable (encapsulates Bike pointer in a BrokenBike object)
	 *
	 * @param b1 Pointer to Bike we want to send to the HashTable
	 */
	void addBike(Bike * b1);

	/**
	 * @brief wrecks Bike with id given as argument
	 *
	 * @param id Integer with ID of the bike we want to wreck
	 * @return Returns true if bike is wrecked successfully and false otherwise
	 */
	void wreckBike(unsigned int id, const Date & d1);

	/**
	 * @brief Remove bike with id
	 *
	 * @param id Integer with ID of the bike we want to remove
	 */
	void removeBike(unsigned int id);

	/**
	 * @brief Remove all bikes that already were wrecked
	 */
	void cleanJunkyard();


	//=========================================================================
	//======================| PRINT |==========================================
	//=========================================================================
	/**
	 * @brief Prints information of every broken bike in brokenBikes
	 * @return void
	 */
	void showAllBikes();

	/**
	 * @brief Prints information of bikes that already were wrecked
	 * @return void
	 */
	void showWreckedBikes();

	/**
	 * @brief Prints information of bikes that weren't wrecked yet
	 * @return void
	 */
	void showNotWreckedBikes();

	/**
	 * @brief Prints information of bikes with type given as argument
	 * @param bikeType String with type of bikes we want to print
	 * @return void
	 */
	void showTypeBikes(string bikeType);

	/**
	 * @brief Prints information of bikes with type given as argument (bikeType) that were already wrecked
	 * @param bikeType String with type of bikes we want to print
	 * @return void
	 */
	void showWreckedTypeBikes(string bikeType);

	/**
	 * @brief Prints information of bikes with type given as argument (bikeType) that weren't wrecked yet
	 * @param bikeType String with type of bikes we want to print
	 * @return void
	 */
	void showNotWreckedTypeBikes(string bikeType);



	//=========================================================================
	//======================| SOME USER OPERATIONS |================================
	//=========================================================================
	/**
	 * @brief Allows user to insert the id of the bike he wishes to wreck
	 */
	void userWreckBike();

	/**
	 * @brief Allows user to insert the id of the bike he wishes to remove
	 */
	void userRemoveBike();

	/**
	 * @brief menu that allows multiple ways of listing the BrokenBikes in the HashTable
	 * @return void
	 */
	void listingsMenu();

	/**
	 * @brief menu to all junkyard related user operations
	 */
	void menu();

	//=========================================================================
	//================================| FILES |================================
	//=========================================================================

	/**
	 * 	@brief Loads the information in a txt file to the HashTable with the broken bikes
	 * 	@return void
	 */
	void loadBrokenBikes();

	/**
	 * @brief Takes information as BrokenBike and returns as a string in order to be saved in a file
	 * @param bb1 BrokenBike with information wanted
	 * @return string with information from BrokenBike b1
	 */
	string brokenBikeToString(BrokenBike bb1);

	/**
	 * @brief Takes information in string format and returns a BrokenBike with the same information
	 * @param bb1 - string with the information needed to create a new BrokenBike
	 * @return BrokenBike with wanted information
	 */
	BrokenBike stringToBrokenBike(string bb1);

	/**
	 * @brief Converts a string of a Bike to an objct of type Bike
	 * @return pointer to a Bike converted from string b1
	 */
	Bike * stringToBike(string b1);

	/**
	 * @brief Saves the information in a txt file from the HashTable brokenBikes
	 * @return void
	 */
	void saveBrokenBikes();

	/**
	 * @brief Reads the last date a bike was wrecked from a txt file and saves it at lastDate attribute
	 */
	void readLastWreckDate();

	/**
	 * @brief Saves the last date a bike was wrecked in a txt file to later use
	 */
	void saveLastWreckDate();

};

//=========================================================================
//================================| OPERATORS |============================
//=========================================================================

/**
 * @brief Organizes information of BrokenBike b1 in a out stream to print at screen
 * @param os ostream which will be updated with BrokenBike b1 information
 * @param b1 BrokenBike b1
 * @return ostream os with the information from BrokenBike b1
 */
std::ostream & operator<<(std::ostream& os, const BrokenBike & b1);


//=========================================================================
//================================| EXCEPTIONS |===========================
//=========================================================================
/**
 * @brief There isn't a bike with given id at the HashTable to wreck or remove
 */
class NotExistentBike
{
private:
	unsigned int id;

public:
	/**
	 * @brief NotExistentBike constructor
	 */
	NotExistentBike(int id){this->id = id;}
	unsigned int getID() {return id;}
};

class NotWreckedBike
{
private:
	unsigned int id;

public:
	/**
	 * @brief NotWreckedBike construvtos
	 */
	NotWreckedBike(int id) {this->id = id;}
	unsigned int getID() {return id;}
};

#endif /* SRC_JUNKYARD_H_ */
