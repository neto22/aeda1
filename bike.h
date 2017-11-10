#ifndef BIKE_H
#define BIKE_H

#include <string>

using namespace std;

//=================================================================
//BIKE//===========================================================
//=================================================================
class Bike
{
protected:
	//vector<Uses> historyUsages;
	static unsigned int bikeID;	/*acho que deviamos tirar o id das bicicletas, nao vai ter utilidade*/
	const unsigned int id;
	unsigned int pricePerHour;	//euros
	unsigned int speed;

public:
	Bike();
	unsigned int getID() const;
	unsigned int getPrice() const;
	virtual string getType() const;
};

//=================================================================
//URBAN//==========================================================
//=================================================================
class Urban : public Bike
{
private:

public:
	Urban();
	string getType() const;

};

//=================================================================
//SIMPLE URBAN//===================================================
//=================================================================
class SimpleUrban : public Bike
{
private: 

public:
	SimpleUrban();
	string getType() const;
};

//=================================================================
//RACE//===========================================================
//=================================================================
class Race : public Bike
{
private:


public:
	Race();
	string getType() const;
};

//=================================================================
//CHILD//==========================================================
//=================================================================
class Child : public Bike
{
private:

public:
	Child();
	string getType() const;
};


#endif
