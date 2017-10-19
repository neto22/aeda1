#ifndef BIKE_H
#define BIKE_H

//=================================================================
//BIKE//===========================================================
//=================================================================
class Bike
{
protected:
	//vector<Uses> historyUsages;
	static unsigned int bikeID;
	const unsigned int id;

public:
	Bike();
	virtual unsigned int getPrice() const;
	unsigned int getID() const;
};

//=================================================================
//URBAN//==========================================================
//=================================================================
class Urban : public Bike
{
private:
	unsigned int pricePerHour;
	unsigned int speed;

public:
	Urban();
	unsigned int getPrice() const ;

};

//=================================================================
//SIMPLE URBAN//===================================================
//=================================================================
class SimpleUrban : public Bike
{
private: 
	unsigned int pricePerHour;
	unsigned int speed;

public:
	SimpleUrban();
	unsigned int getPrice() const;
};

//=================================================================
//RACE//===========================================================
//=================================================================
class Race : public Bike
{
private:
	unsigned int pricePerHour;
	unsigned int speed;

public:
	Race();
	unsigned int getPrice() const;
};

//=================================================================
//CHILD//==========================================================
//=================================================================
class Child : public Bike
{
private:
	unsigned int pricePerHour;
	unsigned int speed;

public:
	Child();
	unsigned int getPrice() const;
};


#endif
