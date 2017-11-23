#pragma once
#include "bike.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//=================================================================
//SharePoint//=====================================================
//=================================================================

/**
 * @brief SharePoint class has a name, x and y coordinates, capacity and a vector with the Bikes (pointers) allocated there
 */
class SharePoint
{
protected:
	string name;
	int x;
	int y;
	unsigned int capacity;
	vector<Bike*> bikes;

public:

	/**
	 * @brief SharePoint constructor
	 * @param name SharePoint's name
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @param capacity maximum number of bikes to have simultaneously at SharePoint
	 */
	SharePoint(string name, int x, int y, unsigned int capacity);

	//get functions

	/**
	 * @return name
	 */
	string getName() const;
	/**
	 * @return x-coordinate
	 */
	int getX() const;
	/**
	 * @return y-coordinate
	 */
	int getY() const;
	/**
	 * @return vector with all the Bikes (pointers) available on this SharePoint
	 */
	vector<Bike*> getBikes() const;
	/**
	 * @return number of Bikes on this SharePoint
	 */
	unsigned int getNumBikes() const;
	/**
	 * @return capacity (maximum Bikes possible to have on this SharePoint)
	 */
	unsigned int getCapacity() const;
	/**
	 * @return percentage of occupancy on this sharepoint
	 */
	unsigned int getPercentageOccupancy() const;

	void clearBikes();

	//boolean and management functions

	/**
	 * @brief checks if SharePoint is full
	 * @return true if it's full
	 * @return false otherwise
	 */
	bool isFull() const;
	/**
	 * @brief removes Bike of bikeType from vector bikes if SharePoint isn't empty
	 * @return true if successful
	 * @return false otherwise
	 */
	bool removeBike(string bikeType);
	/**
	 * @brief adds Bike (pointer) b1 to vector bikes if SharePoint isn't full
	 * @return true if successful
	 * @return false otherwise
	 */
	bool addBike(Bike* b1);

	//counting functions


	/**
	 * @param bikeType type of Bike
	 * @return number of bikes from a specific type (bikeType)
	 */
	unsigned int countBikes(string bikeType) const;

	/**
	 * @brief checks if 2 SharePoints have the same location by comparing their x and y coordinates
	 * if theirs position are the same @return true else @return false
	 */
	//operator to see if 2 SharePoints have the same location
	bool operator == (SharePoint p2);

};

/**
 * @brief converts SharePoint into a string to be saved in file
 *
 *
 * converts SharePoint into a string in the format of:
 * ( x , y ) ; capacity ; ( number_of_urban_bikes ; number_of_simpleurban_bikes ; number_of_race_bikes ; number_of_child_bikes )
 * @return out stream with organized values of SharePoint p1 as string
 */
ostream & operator << (ostream & os, SharePoint p1);


//=================================================================
//Exeptions//======================================================
//=================================================================

