#pragma once
#include "bike.h"
#include "clients.h"
#include <vector>
#include <math.h>


//=================================================================
//SharePoint//=====================================================
//=================================================================
class SharePoint
{
protected:
	double x;
	double y;
	unsigned int capacity;
	vector<Bike*> bikes;

public:
	SharePoint(double x, double y, unsigned int capacity);

	//get functions

	//returns x coordinate
	double getX() const;
	//returns y coordinate
	double getY() const;
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
	bool removeBike(/*to complete*/);	//not done
	//adds a bike, true if sucesseful false otherwise
	bool addBike(Bike* b1);
	//calculates the distance between the sharepoint and another one (given as argument)
	double distance(Client c1);

	//operator to see if 2 SharePoints have the same location
	bool operator == (SharePoint p2);

};

//other operator, that automatically turns a SharePoint into a string
ostream & operator << (ostream & os, SharePoint p1);
