#ifndef BIKE_H
#define BIKE_H

#include <string>

using namespace std;

//=================================================================
//BIKE//===========================================================
//=================================================================

/**
 * @brief Bike class: a Bike has an ID, a price per hour and a type.
 */
class Bike
{
protected:
	//vector<Uses> historyUsages;
	static unsigned int bikeID;	//maybe useful to next part
	const unsigned int id;
	unsigned int pricePerHour;	//euros

public:
	/**
	 * @brief Bike constructor, generates bike ID
	 */
	Bike();
	/**
	* @return Bike's ID
	*/
	unsigned int getID() const;
	/**
	 * @return price per hour
	 */
	unsigned int getPrice() const;
	/**
	 * @return Bike's type
	 */
	virtual string getType() const;
};

//=================================================================
//URBAN//==========================================================
//=================================================================

/**
 * @brief Bike sub-class of the Urban type
 */
class Urban : public Bike
{
private:

public:
	/**
	 * @brief Urban bike constructor, sets price per hour
	 */
	Urban();
	/**
	 * @return Bike's type : "Urban"
	 */
	string getType() const;

};

//=================================================================
//SIMPLE URBAN//===================================================
//=================================================================

/**
 * @brief Bike sub-class of the SimpleUrban type
 */
class SimpleUrban : public Bike
{
private: 

public:
	/**
	 * @brief SimpleUrban bike constructor, sets price per hour
	 */
	SimpleUrban();
	/**
	 * @return Bike's type : "SimpleUrban"
	 */
	string getType() const;
};

//=================================================================
//RACE//===========================================================
//=================================================================
/**
 * @brief Bike sub-class of the Race type
 */
class Race : public Bike
{
private:


public:
	/**
	 * @brief Race bike constructor, sets price per hour
	 */
	Race();
	/**
	 * @return Bike's type : "Race"
	 */
	string getType() const;
};

//=================================================================
//CHILD//==========================================================
//=================================================================
/**
 * @brief Bike sub-class of the Child type
 */
class Child : public Bike
{
private:

public:
	/**
	 * @brief Child bike constructor, sets price per hour
	 */
	Child();
	/**
	 * @return Bike's type : "Child"
	 */
	string getType() const;
};


#endif
