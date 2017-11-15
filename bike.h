#ifndef BIKE_H
#define BIKE_H

#include <string>

using namespace std;

//=================================================================
//BIKE//===========================================================
//=================================================================

/**
 * @brief Bike class: a bike has an ID, a price per hour, a speed value and a type. The bike class is abstract.
 */
class Bike
{
protected:
	//vector<Uses> historyUsages;
	static unsigned int bikeID;	/*acho que deviamos tirar o id das bicicletas, nao vai ter utilidade*/
	const unsigned int id;
	unsigned int pricePerHour;	//euros
	unsigned int speed;

public:
	/**
	 * @brief Bike constructor, generates bike ID
	 */
	Bike();
	/**
	* @return bike ID
	*/
	unsigned int getID() const;
	/**
	 * @return price per hour
	 */
	unsigned int getPrice() const;
	/**
	 * @return bike type
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
	 * @return bike type (urban)
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
	 * @brief Simple urban bike constructor, sets price per hour
	 */
	SimpleUrban();
	/**
	 * @return bike type (simple urban)
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
	 * @return bike type (race)
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
	 * @return bike type (child)
	 */
	string getType() const;
};


#endif
