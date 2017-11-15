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
	int x, y;			//initial coordinates of the client

	//getting the name of the new client
	name = askString("Name: ");


	//getting the type of client that is going to be
	do
	{
		type = askString("Type (Partner/Regular): ");

	}while( (type != "Partner") && (type != "Regular") );

	//getting the coordinates
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	if(type == "Partner")
		addClient(new Partner(name,x,y));
	else
		addClient(new Regular(name,x,y));

}
//DONE AND TESTED
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
	//local variables
	unsigned int currentID;		//users ID
	int x,y;					//user new location
	int index;			//clients index in the vector of clients

	//finding out which user is requesting a location change
	currentID = getInteger("Client ID: ", 1,99999);

	//checking if it exists
	index = findClient(currentID);
	if(index == -1)
		throw(NotExistentClient(currentID));

	//after making sure there is a valid client
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	//updating the clients information with new information
	clients.at(index)->setX(x);
	clients.at(index)->setY(y);

	cout << "Location changed successfully!" << endl;
}
//DONE AND TESTED
void Company::pickBike()
{
	unsigned int ID = getInteger("Client ID:",1,9999999); //can be changed to the static
	string bikeType = askString("Bike Type: ");

	try
	{
		clientPickBike(ID, bikeType);
	}
	catch(NotExistentClient & e)
	{
		cout << "There isn't a client with ID : " << e.getID() << endl;
	}
	catch(ClientAlreadyWithBike & e)
	{
		cout << "Client already has a bike : return before pick another " << endl;
	}
}
//YET TO BE DONE
void Company::returnBike()
{
	unsigned int ID = getInteger("Client ID:",1,9999999); //can be changed to the static

	try
	{
		clientReturnBike(ID);
	}
	catch(NotExistentClient & e)
	{
		cout << "There isn't a client with ID : " << e.getID() << endl;
	}
	catch(ClientWithoutBike & e)
	{
		cout << "Client doesn't have a bike : pick one if you wish " << endl;
	}

}
//DONE AND TESTED
void Company::clientManagementMenu()
{
	//print the menu
	displayClientManagement();

	//get the option
	int option = getInteger("Choose an option: ",1,8);
	switch(option)
	{
	case 1:						//adding a new client to the company
	{
		addingNewClient();
		break;
	}
	case 2:						//removing a client from the company
	{
		removingClient();
		break;
	}
	case 3:						//changing location of a client
	{
		try
		{
			changeClientLocation();
		}
		catch(NotExistentClient & e)
		{
			cout << "There isn't a client with ID : " << e.getID() << endl;
		}
		break;
	}
	case 4:						//atributing a bike to a client
	{
		pickBike();
		break;
	}
	case 5:						//returning a bike back to a sharepoint (from a client)
	{
		returnBike();
		break;
	}
	case 6:
	{
		showClients("Partner");
		break;
	}
	case 7:
	{
		showClients("Regular");
		break;
	}
	case 8:
	{
		cout << "Leaving Clients Management Menu" << endl;
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
//DONE AND TESTED
void Company::addingNewSharePoint()
{
	//local variables
	unsigned int capacity;		//maximum number of bikes in the sharepoint
	int x, y;				//coordinates of the share point

	//getting the coordinates
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);
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
//DONE AND TESTED
void Company::removingSharePoint()
{
	//local variables
	int x, y;				//coordinates of the share point

	//getting the coordinates
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	try
	{
		removeSharePoint(x,y);
	}

	catch(NotExistentSharePoint & e)
	{
		cout << "Location doesn't have a SharePoint : " << e.getInformation() << endl;
	}
}
//DONE AND TESTED
void Company::addingBikeToSharePoint()
{
	//local variables
	string bikeType;
	int x,y;

	//getting the values
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);
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
//DONE AND TESTED
void Company::sharePointManagementMenu()
{
	//local variables
	int option;

	//print the menu
	displaySharePointManagement();

	//get the option
	option = getInteger("Choose an option: ",1,5);
	switch(option)
	{
	case 1:								//adding a new sharepoint to the company
	{
		addingNewSharePoint();
		break;
	}
	case 2:								//removing a sharepoing from the company
	{
		removingSharePoint();
		break;
	}
	case 3:								//adding a bike to a sharepoint (new bike)
	{
		addingBikeToSharePoint();
		break;
	}
	case 4:
	{
		showSharePoints();
		break;
	}
	case 5:
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
//===========================| GET |=======================================
//=========================================================================
//DONE AND TESTED
vector<SharePoint *>  Company::getSharePoints() const
{
	return sharePoints;
}
//DONE AND TESTED
vector<Client *> Company::getClients() const
{
	return clients;
}

//=========================================================================
//===========================| SEARCH |====================================
//=========================================================================
//DONE AND TESTED
int Company::findSharePoint(int x, int y) const
{
	for(size_t i = 0; i < sharePoints.size(); i++)
	{
		if( (sharePoints.at(i)->getX() == x) && (sharePoints.at(i)->getY() == y) )
		{
			return i;
			break;
		}
	}

	return -1;	//didn't find SharePoint
}
//DONE AND TESTED
int Company::findClient(unsigned int clientID) const
{
	//search the client in vector clients
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(clients.at(i)->getID() == clientID)
		{
			return i;	//client found
			break;
		}
	}

	return -1;			//didn't find client with clientID
}


//=========================================================================
//===========================| VECTOR MANAGEMENT |=========================
//=========================================================================
//DONE AND TESTED
void Company::addSharePoint(SharePoint * p1)
{
	for(size_t i = 0; i < sharePoints.size(); i++)
		if( ( sharePoints.at(i)->getX() == p1->getX() ) && ( sharePoints.at(i)->getY() == p1->getY() ))
			throw ExistentSharePoint(p1->getX(), p1->getY());	//sharePoint already exists at this location

	//if there is no sharePoint at this location
	sharePoints.push_back(p1);	//add p1 to sharePoints vector

}
//DONE AND TESTED
void Company::removeSharePoint(int x, int y)
{
	int sharePointIndex = findSharePoint(x,y);	//index of SharePoint to remove from sharePoints vector

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	//if there is a SharePoint at location (x,y) we must remove it
	sharePoints.erase(sharePoints.begin() + sharePointIndex);	//SharePoint (pointer) removed

}
//DONE AND TESTED
void Company::addClient(Client * c1)
{
	clients.push_back(c1);
}
//DONE AND TESTED
void Company::removeClient(unsigned int clientID)
{
	int clientIndex = findClient(clientID);	//index of client we want to find ( =-1 while not found)

	//if client not found
	if(clientIndex == -1)
		throw(NotExistentClient(clientID));

	//if client found
	clients.erase(clients.begin() + clientIndex);
}
//DONE AND TESTED
void Company::addBike(int x, int y, string bikeType)
{
	int sharePointIndex = findSharePoint(x,y);	//index of SharePoint to add Bike (pointer)

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	if((bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child"))
		throw NotExistentBikeType(bikeType);	//bikeType doesn´t exist

	if(sharePoints.at(sharePointIndex)->isFull())
		throw FullSharePoint(x,y);	//SharePoint can´t take more bikes

	//if we have all conditions to add bike
	sharePoints.at(sharePointIndex)->addBike(stringToBike(bikeType));

}
//TO BE TESTED
void Company::showClients(string clientType) const
{
	for(size_t i = 0; i < clients.size(); i++)
		if(clients.at(i)->getType() == clientType)
			cout << clients.at(i)->getInformation() << endl;
}
//TO BE TESTED
void Company::showSharePoints() const
{
	for(size_t i = 0; i < sharePoints.size(); i++)
		cout << *sharePoints.at(i) << endl;
}


//=========================================================================
//==================| PICK AND RETURN BIKES |==============================
//=========================================================================
//DONE AND TESTED
void Company::clientPickBike(unsigned int clientID, string bikeType)
{
	int clientIndex = findClient(clientID);	//index of client we want to find ( =-1 while not found)

	//if client not found
	if(clientIndex == -1)
		throw(NotExistentClient(clientID));


	//if client found
	if(clients.at(clientIndex)->getCurrentBike() != NULL)
		throw ClientAlreadyWithBike();


	try
	{
		SharePoint * p1 = clients.at(clientIndex)->closestSHtoPick(sharePoints, bikeType);
		cout << "Closest SharePoint : " << *p1 << endl;
		cout << "Distance : " << clients.at(clientIndex)->distance(*p1) << endl;

		//allocating bike
		p1->removeBike(bikeType);
		clients.at(clientIndex)->setCurrentBike(stringToBike(bikeType));

		//changing client's position
		clients.at(clientIndex)->setX(p1->getX());
		clients.at(clientIndex)->setY(p1->getY());
	}

	catch(NotAvaibleSharePoints & e)
	{
		cout << "Not Avaible SharePoints with : " << e.getBykeType() << endl;
	}
}

//TO TEST
void Company::clientReturnBike(unsigned int clientID)
{
	int clientIndex = findClient(clientID);	//index of client we want to find ( =-1 while not found)

	//if client not found
	if(clientIndex == -1)
		throw(NotExistentClient(clientID));


	//if client found
	if(clients.at(clientIndex)->getCurrentBike() == NULL)
		throw ClientWithoutBike();

	try
	{
		SharePoint * p1 = clients.at(clientIndex)->closestSHtoReturn(sharePoints);
		cout << "Closest SharePoint : " << *p1 << endl;
		cout << "Distance : " << clients.at(clientIndex)->distance(*p1) << endl;

		unsigned int hours = getInteger("Hours current bike was used:",1,9999);
		clients.at(clientIndex)->pay(hours);

		//allocating bike
		p1->addBike(clients.at(clientIndex)->getCurrentBike());	//add bike (pointer) to sharePoint
		clients.at(clientIndex)->setCurrentBike(NULL);			//"remove" bike from client

		//changing client's position
		clients.at(clientIndex)->setX(p1->getX());
		clients.at(clientIndex)->setY(p1->getY());

	}

	catch(NotAvaibleSharePoints & e)
	{
		cout << "All SharePoints Full" << endl;
	}

}

//TO TEST
void Company::endOfMonth()
{
	for(size_t i=0; i < clients.size(); i++)
		if(clients.at(i)->getType() == "Partner")
			clients.at(i)->payMonth();
}

//=========================================================================
//=======================| FILES MANAGEMENT |==============================
//=========================================================================
//DONE AND TESTED
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
//DONE AND TESTED
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
//DONE AND TESTED
SharePoint * Company::stringToSharePoint(string p1)
{
	string irrelevant;
	int x,y;
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
//DONE AND TESTED
Client * Company::stringToClient(string c1)
{
	string irrelevant, name, type, currentBike;
	int x,y;
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

	result->setCurrentBike(stringToBike(currentBike));

	return result;
}
//DONE AND TESTED
Bike * Company::stringToBike(string b1)
{
	if(b1 == "NONE")
		return NULL;
	else if(b1 == "Urban")
		return (new Urban());
	else if(b1 == "SimpleUrban")
		return (new SimpleUrban());
	else if(b1 == "Race")
		return (new Race());
	else
		return (new Child());
}
//DONE AND TESTED
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
//DONE AND TESTED
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
