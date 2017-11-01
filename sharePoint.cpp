#include "sharePoint.h"


//constructor
SharePoint::SharePoint(double x, double y, unsigned int capacity)
{
	this->x = x;
	this->y = y;
	this->capacity = capacity;
}


//get functions
double SharePoint::getX() const
{
	return x;
}

double SharePoint::getY() const
{
	return y;
}

vector<Bike*> SharePoint::getBikes() const
{
	return bikes;
}

unsigned int SharePoint::getNumBikes() const
{
	return bikes.size();
}

unsigned int SharePoint::getCapacity() const
{
	return capacity;
}

//boolean and management functions
bool SharePoint::isFull() const
{
	if( bikes.size() < capacity )
		return false;
	else
		return true;
}

bool SharePoint::addBike(Bike* b1)
{
	if(!isFull())
	{
		bikes.push_back(b1);
		return true;
	}

	else
		return false;

}

double SharePoint::distance(Client c1)
{
	double xVector = x - c1.getX();
	double yVector = y - c1.getY();

	return sqrt( pow(xVector,2) + pow(yVector,2) );	//return the vector length
}


//operators
bool SharePoint::operator == (SharePoint p2)
{
	if( (x == p2.x) && (y == p2.y) )	//SharePointers have the same location
		return true;
	else
		return false;
}

ostream & operator << (ostream & os, SharePoint p1)
{
	os << "( " << p1.getX() << " , " << p1.getY() << " ) ; " << p1.getCapacity();

	return os;
}
