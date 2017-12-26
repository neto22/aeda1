#include "store.h"

#include <iostream>

using namespace std;

//=========================================================================
//=================| CONSTRUCTORS |========================================
//=========================================================================

Store::Store(string name, vector<Bike *> bikes) : reputation(0)		//not rated yet
{
	this->name = name;
	this->bikes = bikes;
}


//=========================================================================
//=================| GET FUNCTIONS |=======================================
//=========================================================================

string Store::getName() const
{
	return name;
}


double Store::getReputation() const
{
	return reputation;
}


vector<Bike *> Store::getBikes() const
{
	return bikes;
}

/*
vector<int> Store::getRatings() const
{
	return ratings;
}
*/


//=========================================================================
//=================| SET FUNCTIONS |=======================================
//=========================================================================

void Store::setReputation(double reputation)
{
	this->reputation = reputation;
}

void Store::setTotalSumRatings(int totalSumRatings)
{
	this->totalSumRatings = totalSumRatings;
}

void Store::setNumRatings(int numRatings)
{
	this->numRatings = numRatings;
}


//=========================================================================
//=================| CALCULATING FUNCTIONS |===============================
//=========================================================================

int Store::bikesInStock(string bikeType) const
{
	int total = 0;

	for(size_t i = 0; i < bikes.size(); i++)
	{
		if(bikes.at(i)->getType() == bikeType)
			total++;
	}

	return total;
}


void Store::updateReputation()
{
	double res = 0;
/*
	for(int i = 0; i < ratings.size(); i++)
		res += ratings.at(i);

	res /= ratings.size();
*/
	res = (double)totalSumRatings / numRatings;

	reputation = res;
}


//=========================================================================
//=================| BOOLEAN FUNCTIONS |===================================
//=========================================================================

bool Store::hasEnoughStock(string bikeType, int numBikes)
{
	return (bikesInStock(bikeType) >= numBikes);
}


//=========================================================================
//=================| MANAGEMENT FUNCTIONS |================================
//=========================================================================

int Store::sellBikes(string bikeType, int numBikes)
{
	int totalAmmount = 0;
	int bikesCounter = 0;

	vector<Bike *>::iterator it;
	for(it = bikes.begin(); (it != bikes.end()) && (bikesCounter < numBikes) ; it++)
	{
		if((*it)->getType() == bikeType)
		{
			totalAmmount += (*it)->getTotalPrice();
			it = bikes.erase(it);
			it--;
			bikesCounter++;
		}
	}

	return totalAmmount;
}


void Store::addRating(int rating)
{
	totalSumRatings += rating;
	numRatings++;
}


//=========================================================================
//=================| CONVERT |=============================================
//=========================================================================

string Store::storeToString()
{
	string res;

	int numUrban = bikesInStock("Urban"),
		numSimpleUrban = bikesInStock("SimpleUrban"),
		numRace = bikesInStock("Race"),
		numChild = bikesInStock("Child");

	res = name + " ; " + to_string(reputation) + " ; "
			   + to_string(totalSumRatings) + " ; " + to_string(numRatings) + " ; "
			   + to_string(numUrban) + " , " + to_string(numSimpleUrban) + " , " + to_string(numRace) + " , " + to_string(numChild);

	return res;
}


//=========================================================================
//=================| OPERATORS |===========================================
//=========================================================================

bool Store::operator < (const Store & s2) const
{
	return (reputation < s2.reputation);
}


//=========================================================================
//=================| PRINT |===============================================
//=========================================================================

ostream& operator<<(ostream& os, const Store & s1)
{
	os      << "Name:                    " << s1.getName() << endl
			<< "Reputation:              " << s1.getReputation() << endl
			<< "Number Urban Bikes:      " << s1.bikesInStock("Urban") << endl
			<< "Number SimpleUban Bikes: " << s1.bikesInStock("SimpleUrban") << endl
			<< "Number Race Bikes:       " << s1.bikesInStock("Race") << endl
			<< "Number Child Bikes:      " << s1.bikesInStock("Child") << endl;

	return os;
}
