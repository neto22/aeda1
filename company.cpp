#include "company.h"
#include "display.h"
#include "global.h"

//constructor
Company::Company()
{
	//just creates a company so we can save the clients and the sharepoints
}

//=========================================================================
//=================| CLIENT MANAGEMENT |===================================
//=========================================================================
//DONE AND TESTED
void Company::addingNewClient()
{
	//local variables
	string name, type;		//type and name of the new client
	double x, y;			//initial coordinates of the client

	//getting the name of the new client
	name = askString("Name: ");


	//getting the type of client that is going to be
	do
	{
		type = askString("Type (Partner/Regular): ");

	}while( (type != "Partner") && (type != "Regular") );

	//getting the coordinates
	x = getDouble("X Coordinate: ", -1000,1000);
	y = getDouble("Y Coordinate: ", -1000,1000);

	if(type == "Partner")
		addClient(new Partner(name,x,y));
	else
		addClient(new Regular(name,x,y));

}

void Company::removingClient()
{
	unsigned int ID = getInteger("Client ID:",1,9999999); //can be changed to the static
	try
	{
		removeClient(ID);
	}
	catch(NotExistentClient & e)
	{
		cout << "There isn't a client with ID : " << e.getID() << endl;
	}
}
//YET TO BE DONE
void Company::changeClientLocation()
{

}
//YET TO BE DONE
void Company::pickBike()
{

}
//YET TO BE DONE
void Company::returnBike()
{

}

void Company::clientManagementMenu()
{
	//print the menu
	displayClientManagement();

	//get the option
	int option = getInteger("Choose an option: ",1,6);
	switch(option)
	{
	case 1:
	{
		addingNewClient();
		break;
	}
	case 2:
	{
		removingClient();
		break;
	}
	case 3:
	{
		changeClientLocation();
		break;
	}
	case 4:
	{
		pickBike();
		break;
	}
	case 5:
	{
		returnBike();
		break;
	}
	case 6:
	{
		cout << "Leaving Share Point Management Menu" << endl;
		break;
	}
	default:
	{
		//it never gets to default since the menu option is delimited by getInteger()
	}
	}
}

//=========================================================================
//================| SHARE POINT MANAGEMENT |===============================
//=========================================================================
//DONE
void Company::addingNewSharePoint()
{
	//local variables
	unsigned int capacity;		//maximum number of bikes in the sharepoint
	double x, y;				//coordinates of the share point

	//getting the coordinates
	x = getDouble("X Coordinate: ", -1000,1000);
	y = getDouble("Y Coordinate: ", -1000,1000);
	capacity = getInteger("Capacity: ", 1, 500);

	try
	{
		addSharePoint(new SharePoint(x,y,capacity));
	}

	catch(ExistentSharePoint & e)
	{
		cout << "Location Already Occupied : " << e.getInformation() << endl;
	}
}
//DONE
void Company::removingSharePoint()
{
	//local variables
	double x, y;				//coordinates of the share point

	//getting the coordinates
	x = getDouble("X Coordinate: ", -1000,1000);
	y = getDouble("Y Coordinate: ", -1000,1000);

	try
	{
		removeSharePoint(x,y);
	}

	catch(NotExistentSharePoint & e)
	{
		cout << "Location doesn't have a SharePoint : " << e.getInformation() << endl;
	}
}

void Company::addingBikeToSharePoint()
{
	//local variables
	string bikeType;
	double x,y;

	//getting the values
	x = getDouble("X Coordinate: ", -1000,1000);
	y = getDouble("Y Coordinate: ", -1000,1000);
	bikeType = askString("Bike Type: ");

	//try to create the sharepoint
	try
	{
	addBike(x, y, bikeType);
	}

	catch(NotExistentSharePoint & e)
	{
	cout << "SharePoint does not exist : ( " << e.getInformation() << endl;
	}

	catch(NotExistentBikeType & e)
	{
		cout << "No such Bike Type : " << e.getType() << endl;
	}

	catch(FullSharePoint & e)
	{
		cout << "Full SharePoint : ( " << e.getX() << " , " << e.getY() << " ) " << endl;
	}
}

void Company::sharePointManagementMenu()
{
	//local variables
	int option;

	do
	{
		//print the menu
		displaySharePointManagement();

		//get the option
		option = getInteger("Choose an option: ",1,4);
		switch(option)
		{
		case 1:
		{
			addingNewSharePoint();
			break;
		}
		case 2:
		{
			removingSharePoint();
			break;
		}
		case 3:
		{
			addingBikeToSharePoint();
			break;
		}
		case 4:
		{
			cout << "Leaving Share Point Management Menu" << endl;
			break;
		}
		default:
		{
			//it never gets to default since the menu option is delimited by getInteger()
		}
		}
	}while(option != 4);

}

//=========================================================================
//===========================| GET |=======================================
//=========================================================================
vector<SharePoint *>  Company::getSharePoints() const
{
	return sharePoints;
}

vector<Client *> Company::getClients() const
{
	return clients;
}


//=========================================================================
//===========================| VECTOR MANAGEMENT |=========================
//=========================================================================
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


//=========================================================================
//=======================| FILES MANAGEMENT |==============================
//=========================================================================
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
