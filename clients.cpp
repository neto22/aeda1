#include "clients.h"	/*only enough to work at SharePoint and Company*/

//static

unsigned int Client::id_counter = 1;

//=================================================================
//Client//=========================================================
//=================================================================

//constructors
Client::Client(string name, int x, int y)	: user_id(id_counter)
{
	this->name = name;
	this->x = x;
	this->y = y;

	id_counter++;
}

//get functions

unsigned int Client::getID() const
{
	return user_id;
}

string Client::getName() const
{
	return name;
}

int Client::getX() const
{
	return x;
}

int Client::getY() const
{
	return y;
}

string Client::getType() const
{
	return ""; //only runs Partner or Reguler function
}

string Client::getInformation() const
{
	return "";	//only will run Partner or Regular function
}

Bike * Client::getCurrentBike() const
{
	return currentBike;
}

//set functions

void Client::setID(unsigned int user_id)
{
	this->user_id = user_id;
}

void Client::setX(int x)
{
	this->x = x;
}

void Client::setY(int y)
{
	this->y = y;
}

void Client::setCurrentBike(Bike * b1)
{
	this->currentBike = b1;
}

//distance to sharePoints
double Client::distance(SharePoint p1)
{
	double xVector = x - p1.getX();
	double yVector = y - p1.getY();

	return sqrt( pow(xVector,2) + pow(yVector,2) );	//return the vector length
}

SharePoint * Client::closestSHtoReturn(const vector<SharePoint *> & sharePoints)
{
	int firstMin = -1, sharePointInd;
	double minDistance;

	//check if there is at least one avaible SharePoint (with first minDistance)
	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if(!sharePoints.at(i)->isFull())
		{
			firstMin = i;
			sharePointInd = i;
			minDistance = distance(*sharePoints.at(i));
			break;
		}
	}

	if(firstMin == -1)
		throw NotAvaibleSharePoints();

	//already exists one avaible SharePoint, see if there's other closest to client
	for(size_t i = firstMin; i < sharePoints.size(); i++)
	{
		if(!sharePoints.at(i)->isFull())
		{
			double newDistance = distance(*sharePoints.at(i));

			if(newDistance < minDistance)
			{
					minDistance = newDistance;
					sharePointInd = i;
			}
		}
	}


	return sharePoints.at(sharePointInd);
}

SharePoint * Client::closestSHtoPick(const vector<SharePoint *> & sharePoints, string bikeType)
{
	int firstMin, sharePointInd;
	double minDistance;
	bool presentType = false;

	//check if there is at least one SharePoint with bikeType
	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		//search bike type at bikes from the SharePoint
		for(size_t j = 0; j < sharePoints.at(i)->getBikes().size(); j++)
		{
			if(sharePoints.at(i)->getBikes().at(j)->getType() == bikeType)
			{
				presentType = true;
				firstMin = i;
				sharePointInd = i;
				minDistance = distance(*sharePoints.at(i));
				break;
			}
		}

		if(presentType)
			break;
	}

	//bikeType not found in any SharePoint
	if(!presentType)
		throw NotAvaibleSharePoints(bikeType);

	for(size_t i = firstMin; i < sharePoints.size(); i++)
	{
		//search bike type at bikes from the SharePoint
		for(size_t j = 0; j < sharePoints.at(i)->getBikes().size(); j++)
		{
			presentType = false;

			if(sharePoints.at(i)->getBikes().at(j)->getType() == bikeType)
			{
				presentType = true;
				double newDistance = distance(*sharePoints.at(i));

				if(newDistance < minDistance)
				{
					minDistance = newDistance;
					sharePointInd = i;
				}

				break;

			}

			if(presentType)
				break;
		}
	}

	return sharePoints.at(sharePointInd);
}

//payment functions
void Client::pay(unsigned int hours)
{
	//will only run partner or regular pay
}

void Client::payMonth()
{
	//will only run partner payMonth
}

//=================================================================
//Partner//========================================================
//=================================================================

//constructor
Partner::Partner(string name, int x, int y) : Client(name, x, y)
{
	monthPayment = 10;
}

//get functions
string Partner::getInformation() const
{
	string result;

	result = "Partner ; " + to_string(user_id) + " ; " + name + " ; ( " + to_string(x) + " , " + to_string(y) + " ) ; ";

	if(currentBike == NULL)
		result = result + "NONE";
	else
		result = result + currentBike->getType();

	return result;
}

string Partner::getType() const
{
	return "Partner"; //only runs Partner or Regular function
}

//payment functions
void Partner::pay(unsigned int hours)
{
	bikesPayment = bikesPayment + currentBike->getPrice()*hours;	//nos discounted yet
	hoursMonth = hoursMonth + hours;
}

void Partner::payMonth()
{
	unsigned int price;		//total value to pay, with discounts

	if(hoursMonth > 20)
		price = monthPayment + 0.90*bikesPayment;	//10% discount
	else
		price = monthPayment + 0.95*bikesPayment;	//5% discount

	cout << name << " pays : " << price << " euros" << endl;

	bikesPayment = 0;	//reset bikesPayment
	hoursMonth = 0;		//reset hoursMonth
}

//=================================================================
//Regular//========================================================
//=================================================================

//constructor
Regular::Regular(string name, int x, int y) : Client(name, x, y)
{

}

//get functions
string Regular::getInformation() const
{
	string result;

	result = "Regular ; " + to_string(user_id) + " ; " + name + " ; ( " + to_string(x) + " , " + to_string(y) + " ) ; ";

	if(currentBike == NULL)
		result = result + "NONE";
	else
		result = result + currentBike->getType();

	return result;
}

string Regular::getType() const
{
	return "Regular"; //only runs Partner or Reguler function
}

//payment functions
void Regular::pay(unsigned int hours)
{
	cout << name << " pays : " << currentBike->getPrice()*hours << endl;
}

//=================================================================
//Operators//======================================================
//=================================================================
