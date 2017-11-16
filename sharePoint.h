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
 * @brief SharePoint class has x and y coordinates, capacity and a vector with the bikes allocated there
 */
class SharePoint
{
protected:
	int x;
	int y;
	unsigned int capacity;
	vector<Bike*> bikes;

public:

	/**
	 * @brief SharePoint constructor
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @param capacity maximum bikes to have simultaneous at SharePoint
	 */
	SharePoint(int x, int y, unsigned int capacity);

	//get functions

	/**
	 * @return x-coordinate
	 */
	int getX() const;
	/**
	 * @return y-coordinate
	 */
	int getY() const;
	/**
	 * @return vector with all the bikes available on this SharePoint
	 */
	vector<Bike*> getBikes() const;
	/**
	 * @return number of bikes on this SharePoint
	 */
	unsigned int getNumBikes() const;
	/**
	 * @return capacity (maximum bikes possible to have on this SharePoint)
	 */
	unsigned int getCapacity() const;
	/**
	 * @return percentage of occupancy on this sharepoint
	 */
	unsigned int getPercentageOccupancy() const;

	//boolean and management functions

	/**
	 * @brief checks if SharePoint is full
	 * if there's space available @return false else @return true
	 */
	bool isFull() const;
	/**
	 * @brief removes bike to vector bikes if SharePoint isn't empty
	 * if successful @return true else @return false
	 */
	bool removeBike(string bikeType);
	/**
	 * @brief adds bike to vector bikes if SharePoint isn't full
	 * if successful @return true else @return false
	 */

	bool addBike(Bike* b1);

	//counting functions


	/**
	 * @param bikeType type of bike
	 * @return number of bikes from a specific type
	 */
	unsigned int countBikes(string bikeType) const;

	/**
	 * @brief checks if 2 SharePoints are the same by comparing their x and y coordinates
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
 * @return out stream with organized values of sharepoint as string
 */
ostream & operator << (ostream & os, SharePoint p1);


//=================================================================
//Exeptions//======================================================
//=================================================================

