#include "clients.h"	/*only enough to work at SharePoint and Company*/

//static

unsigned int Client::id_counter = 1;

//constructors
Client::Client(string name, double x, double y)	: user_id(id_counter)
{
	this->name = name;
	this->x = x;
	this->y = y;

	id_counter++;
}

Partner::Partner(string name, double x, double y) : Client(name, x, y)
{
	Client::setType(1);
}

Regular::Regular(string name, double x, double y) : Client(name, x, y)
{
	Client::setType(2);
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

double Client::getX() const
{
	return x;
}


double Client::getY() const
{
	return y;
}

int Client::getType() const
{
	return type;
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

void Client::setX(double x)
{
	this->x = x;
}

void Client::setY(double y)
{
	this->y = y;
}

void Client::setType(int type)
{
	this->type = type;
}

void Client::setCurrentBike(Bike * b1)
{
	this->currentBike = b1;
}

//other functions

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

SharePoint * Client::closestSHtoPeek(const vector<SharePoint *> & sharePoints, string bikeType)
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

//operator

ostream & operator << (ostream & os, Client c1)
{
	if(c1.getType() == 1)
		os << "Partner";
	else
		os << "Regular";

	os << " ; " << to_string(c1.getID()) << " ; " << c1.getName() << " ; ( " << to_string(c1.getX()) << " , " << to_string(c1.getY()) << " )";

	os << " ; ";
	if(c1.getCurrentBike() == NULL)
		os << "NONE";
	else
		os << c1.getCurrentBike()->getType();

	return os;
}
