#include "bike.h"

//this needs to be updated when the program restarts (saved in file)
unsigned int Bike::bikeID = 0;


//=================================================================
//BIKE//===========================================================
//=================================================================
Bike::Bike() : id(bikeID)
{
	bikeID++;
}

unsigned int Bike::getPrice() const
{
	return 0;
}

unsigned int Bike::getID() const
{
	return id;
}

string Bike::getType() const
{
	return "NONE";
}


//=================================================================
//URBAN//==========================================================
//=================================================================
Urban::Urban() : Bike()
{

}

unsigned int Urban::getPrice() const
{
	return pricePerHour;
}

string Urban::getType() const
{
	return "Urban";
}

//=================================================================
//SIMPLE URBAN//===================================================
//=================================================================
SimpleUrban::SimpleUrban() : Bike()
{

}

unsigned int SimpleUrban::getPrice() const
{
	return pricePerHour;
}

string SimpleUrban::getType() const
{
	return "SimpleUrban";
}

//=================================================================
//RACE//===========================================================
//=================================================================
Race::Race() : Bike()
{

}

unsigned int Race::getPrice() const
{
	return pricePerHour;
}

string Race::getType() const
{
	return "Race";
}

//=================================================================
//CHILD//==========================================================
//=================================================================
Child::Child() : Bike()
{

}

unsigned int Child::getPrice() const
{
	return pricePerHour;
}

string Child::getType() const
{
	return "Child";
}
