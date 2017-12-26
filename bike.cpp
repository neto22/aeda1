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
	return pricePerHour;
}

unsigned int Bike::getTotalPrice() const
{
	return totalPrice;
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
	pricePerHour = 30;
	totalPrice = 300;
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
	pricePerHour = 20;
	totalPrice = 200;
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
	pricePerHour = 50;
	totalPrice = 500;
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
	pricePerHour = 10;
	totalPrice = 100;
}

string Child::getType() const
{
	return "Child";
}
