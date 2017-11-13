#include "company.h"

//constructor
Company::Company()
{
	//just creates a company so we can save the clients and the sharepoints
}


//get functions
vector<SharePoint *>  Company::getSharePoints() const
{
	return sharePoints;
}

vector<Client *> Company::getClients() const
{
	return clients;
}


//vectors management
void Company::addSharePoint(SharePoint * p1)
{
	for(size_t i = 0; i < sharePoints.size(); i++)
		if( ( sharePoints.at(i)->getX() == p1->getX() ) && ( sharePoints.at(i)->getY() == p1->getY() ))
			throw ExistentSharePoint(p1->getX(), p1->getY());	//sharePoint already exists at this location

	//if there is no sharePoint at this location
	sharePoints.push_back(p1);	//add p1 to sharePoints vector

}

void Company::removeSharePoint(double x, double y)
{
	int sharePointIndex = -1;	//index of SharePoint to remove from sharePoints vector

	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if( (sharePoints.at(i)->getX() == x) && (sharePoints.at(i)->getY() == y) )
		{
			sharePointIndex = i;
			continue;
		}
	}

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	//if there is a SharePoint at location (x,y) we must remove it
	sharePoints.erase(sharePoints.begin() + sharePointIndex);	//SharePoint (pointer) removed

}

void Company::addClient(Client * c1)
{
	clients.push_back(c1);
}

void Company::removeClient(unsigned int clientID)
{
	int clientIndex = -1;	//index of client we want to find ( =-1 while not found)

	//search the client in vector clients
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(clients.at(i)->getID() == clientID)
		{
			clientIndex = i;	//client found
			break;
		}
	}

	//if client not found
	if(clientIndex == -1)
		throw(NotExistentClient(clientID));

	//if client found
	clients.erase(clients.begin() + clientIndex);
}


void Company::addBike(double x, double y, string bikeType)
{
	int sharePointIndex = -1;	//index of SharePoint to add Bike (pointer)

	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if( (sharePoints.at(i)->getX() == x) && (sharePoints.at(i)->getY() == y) )
		{
			sharePointIndex = i;
			continue;
		}
	}

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	if((bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child"))
		throw NotExistentBikeType(bikeType);	//bikeType doesn´t exist

	if(sharePoints.at(sharePointIndex)->isFull())
		throw FullSharePoint(x,y);	//SharePoint can´t take more bikes

	if(bikeType == "Urban")
		sharePoints.at(sharePointIndex)->addBike(new Urban());
	else if(bikeType == "SimpleUrban")
		sharePoints.at(sharePointIndex)->addBike(new SimpleUrban());
	else if(bikeType == "Race")
			sharePoints.at(sharePointIndex)->addBike(new SimpleUrban());
	else if(bikeType == "Child")
			sharePoints.at(sharePointIndex)->addBike(new SimpleUrban());

}


//files' management
void Company::saveSharePoints(ostream & outFile)
{
	outFile << "/* ( x , y ) ; capacity ; ( Urban , SimpleUrban , Race , Child ) */" << endl << endl;

	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if(i != 0)
			outFile << endl;

		outFile << *sharePoints.at(i);
	}
}

void Company::saveClients(ostream & outFile)
{
	outFile << "/* Type ; ID ; Name ; ( x , y ) ; Current Bike */" << endl << endl;

	for(size_t i = 0; i < clients.size(); i++)
	{
		if(i != 0)
			outFile << endl;

		outFile << clients.at(i)->getInformation();
	}
}

SharePoint * Company::stringToSharePoint(string p1)
{
	string irrelevant;
	double x,y;
	unsigned int capacity, numUrban, numSimpleUrban, numRace, numChild;

	istringstream iStr(p1);

	iStr >> irrelevant >> x >> irrelevant >> y >> irrelevant >> irrelevant >> capacity >> irrelevant >> irrelevant;
	iStr >> numUrban >> irrelevant >> numSimpleUrban >> irrelevant >> numRace >> irrelevant >> numChild;

	SharePoint * result = new SharePoint(x,y,capacity);

	for(size_t i = 0; i < numUrban; i++)
		result->addBike(new Urban());

	for(size_t i = 0; i < numSimpleUrban; i++)
		result->addBike(new SimpleUrban());

	for(size_t i = 0; i < numRace; i++)
		result->addBike(new Race());

	for(size_t i = 0; i < numChild; i++)
		result->addBike(new Child());


	return result;
}

Client * Company::stringToClient(string c1)
{
	string irrelevant, name, type, currentBike;
	double x,y;
	unsigned int id;
	char next;

	istringstream iStr(c1);

	iStr >> type >> irrelevant >> id >> irrelevant;

	iStr.get(next);
	while (next != ';')
	{
		name = name + next;
		iStr.get(next);

	} 	//saving name at string name

	name = name.substr(1, name.length() - 2); //removing spaces before and after name

	iStr >> irrelevant >> x >> irrelevant >> y >> irrelevant >> irrelevant >> currentBike;

	Client * result;

	if(type ==  "Partner")
		result = new Partner(name, x, y);
	else
		result = new Regular(name, x, y);

	result->setID(id);

	if(currentBike == "NONE")
		result->setCurrentBike(NULL);
	else if(currentBike == "Urban")
		result->setCurrentBike(new Urban());
	else if(currentBike == "SimpleUrban")
		result->setCurrentBike(new SimpleUrban());
	else if(currentBike == "Race")
		result->setCurrentBike(new Race());
	else
		result->setCurrentBike(new Child());


	return result;
}

void Company::readSharePoints(istream & inFile)
{
	string irrelevant;

	getline(inFile, irrelevant); getline(inFile, irrelevant);	//two lines before SharePoints' information

	while(!inFile.eof())
	{
		string p1;

		getline(inFile, p1);
		sharePoints.push_back(stringToSharePoint(p1));
	}
}

void Company::readClients(istream & inFile)
{
	string irrelevant;

	getline(inFile, irrelevant); getline(inFile, irrelevant);	//two lines before SharePoints' information

	while(!inFile.eof())
	{
		string c1;

		getline(inFile, c1);
		clients.push_back(stringToClient(c1));
	}

	if(clients.empty())
		Client::id_counter = 1;
	else
		Client::id_counter = clients.at(clients.size()-1)->getID() + 1;

}
