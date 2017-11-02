#include "company.h"

//constructor
Company::Company()
{
	//just creates a company so we can save the clients and the sharepoints
}


//get functions
vector<SharePoint *> Company::getSharePoints() const
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
		if(*sharePoints.at(i) == *p1)
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


//closest SharePoints
/*SharePoint * Company::closestSHtoReturn(unsigned int clientID)
{

	int clientIndex = -1;	//index of client we want to find ( =-1 while not found)
	int sharePointIndex = 0;	//will save the index of the return value (element of vector sharePoints

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
	double shorterDistance = sharePoints.at(0)->distance(*clients.at(clientID));

	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		double newDistance;
		newDistance = sharePoints.at(i)->distance(*clients.at(clientID));

		if(newDistance < shorterDistance)
			sharePointIndex = i;
	}

	return sharePoints.at(sharePointIndex);
}*/



//files' management
void Company::saveSharePoints(ostream & outFile)
{
	outFile << "/* ( x , y ) ; capacity */" << endl << endl;

	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if(i != 0)
			outFile << endl;

		outFile << *sharePoints.at(i);
	}
}

void Company::saveClients(ostream & outFile)
{
	outFile << "/* Type ; Name ; Id ; ( x , y ) */" << endl << endl;

	for(size_t i = 0; i < clients.size(); i++)
	{
		if(i != 0)
			outFile << endl;

		outFile << *clients.at(i);
	}
}

SharePoint * Company::stringToSharePoint(string p1)
{
	string irrelevant;
	double x,y;
	unsigned int capacity;

	istringstream iStr(p1);

	iStr >> irrelevant >> x >> irrelevant >> y >> irrelevant >> irrelevant >> capacity;

	return ( new SharePoint(x,y,capacity) );
}

Client * Company::stringToClient(string c1)
{
	string irrelevant, name, type;
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

	iStr >> irrelevant >> x >> irrelevant >> y;

	if(type ==  "Partner")
		return (new Partner(name, x, y));
	else
		return (new Regular(name, x, y));
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
}
