#pragma once
#include "bike.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//=================================================================
//SharePoint//=====================================================
//=================================================================
class SharePoint
{
protected:
	int x;
	int y;
	unsigned int capacity;
	vector<Bike*> bikes;

public:
	SharePoint(int x, int y, unsigned int capacity);

	//get functions

	//returns x coordinate
	int getX() const;
	//returns y coordinate
	int getY() const;
	//returns the vector of bikes on the share point
	vector<Bike*> getBikes() const;
	//returns the number of bikes on the share point
	unsigned int getNumBikes() const;
	//returns the capacity of the share point
	unsigned int getCapacity() const;

	//boolean and management functions

	//checks if the share point is full
	bool isFull() const;
	//removes a bike and if sucessuful on doing so returns true, false otherwise
	bool removeBike(string bikeType);	//not done
	//adds a bike, true if sucesseful false otherwise
	bool addBike(Bike* b1);

	//counting functions

	//return number of bikes of type bikeType
	unsigned int countBikes(string bikeType) const;

	//operator to see if 2 SharePoints have the same location
	bool operator == (SharePoint p2);

};

//other operator, that automatically turns a SharePoint into a string
ostream & operator << (ostream & os, SharePoint p1);


//=================================================================
//Exeptions//======================================================
//=================================================================

