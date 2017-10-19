#pragma once
#include "bike.h"
#include <vector>

using namespace std;

//=================================================================
//BIKE//===========================================================
//=================================================================
class SharePoint
{
protected:
	unsigned int x;
	unsigned int y;
	unsigned int capacity;
	vector<Bike*> bikes;

public:
	SharePoint(unsigned int x, unsigned int y);

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
	//checks if the share point is full
	bool isFull() const;
	//removes a bike and if sucessuful on doing so returns true, false otherwise
	bool removeBike();
	//adds a bike, true if sucesseful false otherwise
	bool addBike();
	//calculates the distance between the sharepoint and another one (given as argument)
	unsigned double distance(SharePoint p1);


};
