#include "company.h"
#include "display.h"
#include "global.h"
#include <iomanip>

//constructor
Company::Company()
{
	//just creates a company so we can save the clients and the sharepoints
}

//=========================================================================
//=================| CLIENT MANAGEMENT |===================================
//=========================================================================
//DONE AND TESTED
void Company::tryAddNewClient()
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
void Company::tryRemoveClient()
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
//DONE AND TESTED
void Company::tryChangeClientLocation()
{
	//local variables
	unsigned int currentID;		//users ID
	int x,y;					//user new location

	//finding out which user is requesting a location change
	currentID = getInteger("Client ID: ", 1,99999);
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	try
	{
		changeClientLocation(currentID, x,y);
	}
	catch(NotExistentClient & e)
	{
		cout << "There isn't a client with ID : " << e.getID() << endl;
	}

}
//DONE AND TESTED
void Company::tryPickBike()
{
	unsigned int ID = getInteger("Client ID:",1,9999999); //can be changed to the static
	string bikeType;

	do
	{
		bikeType = askString("Bike (Urban/SimpleUrban/Race/Child): ");

	}while((bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child"));


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
//DONE AND TESTED
void Company::tryReturnBike()
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
		tryAddNewClient();
		break;
	}
	case 2:						//removing a client from the company
	{
		tryRemoveClient();
		break;
	}
	case 3:						//changing location of a client
	{
		tryChangeClientLocation();
		break;
	}
	case 4:						//atributing a bike to a client
	{
		tryPickBike();
		break;
	}
	case 5:						//returning a bike back to a sharepoint (from a client)
	{
		tryReturnBike();
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
void Company::tryAddNewSharePoint()
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
void Company::tryRemoveSharePoint()
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
void Company::tryAddBikeToSharePoint()
{
	//local variables
	string bikeType;
	int x,y;

	//getting the values
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	do
	{
		bikeType = askString("Bike Type (Urban/SimpleUrban/Race/Child) : ");

	}while( (bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child") );

	//try to add bike to sharepoint
	try
	{
		addBike(x, y, bikeType);
	}

	catch(NotExistentSharePoint & e)
	{
		cout << "SharePoint does not exist : " << e.getInformation() << endl;
	}

	catch(FullSharePoint & e)
	{
		cout << "Full SharePoint : ( " << e.getX() << " , " << e.getY() << " ) " << endl;
	}
}
//DONE AND TESTED
void Company::tryRemoveBikeFromSharePoint()
{
	//local variables
	string bikeType;
	int x,y;

	//getting the values
	x = getInteger("X Coordinate: ", -1000,1000);
	y = getInteger("Y Coordinate: ", -1000,1000);

	do
	{
		bikeType = askString("Bike Type (Urban/SimpleUrban/Race/Child) : ");

	}while( (bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child") );

	try
	{
		removeBike(x,y,bikeType);
	}
	catch(NotExistentSharePoint & e)
	{
		cout << "SharePoint does not exist : " << e.getInformation() << endl;
	}
	catch(NotExistentBikeType & e)
	{
		cout << "SharePoint does not have bike type : " << e.getType() << endl;
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
	option = getInteger("Choose an option: ",1,6);
	switch(option)
	{
	case 1:								//adding a new sharepoint to the company
	{
		tryAddNewSharePoint();
		break;
	}
	case 2:								//removing a sharepoing from the company
	{
		tryRemoveSharePoint();
		break;
	}
	case 3:								//adding a bike to a sharepoint (new bike)
	{
		tryAddBikeToSharePoint();
		break;
	}
	case 4:
	{
		tryRemoveBikeFromSharePoint();
		break;
	}
	case 5:
	{
		showSharePoints();
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
 //================| SHARE POINT ANALYSIS |===============================
 //=========================================================================
//DONE AND TESTED
void Company::printAllBikesAvailable()
{
	//local variables
	int totUrban = 0, totSimpleUrban = 0, totRace = 0, totChild = 0;	 //initiating all the counters to zero
	string type;

	//loop all the sharepoints and saving the available bikes
	for(unsigned int i = 0; i < sharePoints.size();i++)
	{
		//for each sharepoint increment the number of bikes of each type
		totUrban += sharePoints.at(i)->countBikes("Urban");
		totSimpleUrban += sharePoints.at(i)->countBikes("SimpleUrban");
		totRace += sharePoints.at(i)->countBikes("Race");
		totChild += sharePoints.at(i)->countBikes("Child");
	}
	//after counting it all up, display the results
	cout << endl;
	cout << "Bikes Available:" << endl;
	cout << "Urban:        " << totUrban << endl;
	cout << "Simple Urban: " << totSimpleUrban	<< endl;
	cout << "Race:         " << totRace << endl;
	cout << "Child:        " << totChild << endl;
	cout << "Total:        " << totUrban + totSimpleUrban + totRace + totChild << endl;

}
//DONE AND TESTED
void Company::printOrderedByOccupancy()
{
	//local variables
	string option;									//choosing either crescent or decrescent order to sort by
	vector <SharePoint *> result;					//vector that is going to get printe
	vector <SharePoint *> temporary = sharePoints;	//copy of the original
	int index;

	//choose if wants to be ordered incresing occupancy or decreasing
	do
	{
		option = askString("Order?(Decrescent/Crescent): ");
	}while(option != "Decrescent" && option != "decrescent" && option != "Crescent" && option != "crescent");

	//sort the temporary vetor acordingly
	if(option == "Decrescent" || option == "decrescent")
	{
		//order by decrescent order (HIGH TO LOW)
		for(unsigned int i = 0 ; i < sharePoints.size(); i++)
		{
			unsigned int max = temporary.at(0)->getPercentageOccupancy();
			//for each iteration get the highest value for occupancy in temporary and get it into result
			for(unsigned int j = 0; j < temporary.size(); j++)
			{
				if(temporary.at(j)->getPercentageOccupancy() >= max)
				{
					max = temporary.at(j)->getPercentageOccupancy();
					index = j;
				}
			}

			result.push_back(temporary.at(index));
			temporary.erase(temporary.begin()+index);
		}

	}
	else
	{
		//order by crescent order (LOW TO HIGH)
		for(unsigned int i = 0; i < sharePoints.size();i++)
		{
			unsigned int min = temporary.at(0)->getPercentageOccupancy();

			for(unsigned int j = 0; j < temporary.size();j++)
			{
				if(temporary.at(j)->getPercentageOccupancy() <= min)
				{
					min = temporary.at(j)->getPercentageOccupancy();
					index = j;
				}
			}

			result.push_back(temporary.at(index));
			temporary.erase(temporary.begin()+index);
		}
	}

	//after getting the vector ordered display the values
	for(unsigned int i = 0 ; i < result.size(); i++)
	{
		cout << setw(3) << result.at(i)->getPercentageOccupancy() << "% :" << *(result.at(i)) << endl;
	}

}
//DONE AND TESTED
void Company::printOrderedByTotalBikes()
{
	//local variables
	string option;
	vector <SharePoint *> temporary = sharePoints;
	vector <SharePoint *> result;
	int index;

	do
	{
		option = askString("Order(Crescent/Decrescent)? ");
	}while(option != "Decrescent" && option != "decrescent" && option != "Crescent" && option != "crescent");

	if(option == "Decrescent" || option == "decrescent")
	{
		//order by decrescent order (HIGH TO LOW)
		for(unsigned int i = 0 ; i < sharePoints.size(); i++)
		{
			unsigned int max = temporary.at(0)->getNumBikes();
			//for each iteration get the highest value for occupancy in temporary and get it into result
			for(unsigned int j = 0; j < temporary.size(); j++)
			{
				if(temporary.at(j)->getNumBikes() >= max)
				{
					max = temporary.at(j)->getNumBikes();
					index = j;
				}
			}

			result.push_back(temporary.at(index));
			temporary.erase(temporary.begin()+index);
		}

	}
	else
	{
		//crescent mode
		//order by crescent order (LOW TO HIGH)
		for(unsigned int i = 0; i < sharePoints.size();i++)
		{
			unsigned int min = temporary.at(0)->getNumBikes();

			for(unsigned int j = 0; j < temporary.size();j++)
			{
				if(temporary.at(j)->getNumBikes() <= min)
				{
					min = temporary.at(j)->getNumBikes();
					index = j;
				}
			}

			result.push_back(temporary.at(index));
			temporary.erase(temporary.begin()+index);
		}
	}

	//print the results
	for(unsigned int i = 0 ; i < result.size(); i++)
	{
		cout << setw(3) << result.at(i)->getNumBikes() << " :" << *(result.at(i)) << endl;
	}

}

void Company::sharePointAnalysisMenu()
{
	//local variables
	int option;

	//print the menu
	displaySharePointAnalysis();

	//choose the option
	option = getInteger("Choose option: ",1,6);
	switch(option)
	{
	case 1:					//bikes available (all of them and by types)
	{
		printAllBikesAvailable();
		break;
	}
	case 2:					//sharepoint ordered by % of occupancy
	{
		printOrderedByOccupancy();
		break;
	}
	case 3:					//sharepoints ordered by total number of bikes
	{
		printOrderedByTotalBikes();
		break;
	}
	case 4: 				//brief statistic analysis
	{
		//code
		break;
	}
	case 5:					//redistribute bikes
	{
		//code
		break;
	}
	case 6:					//back to main menu
	{
		cout << "Leaving SharePoint Analysis Menu" << endl;
		break;
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
		if(*sharePoints.at(i) == *p1)
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
void Company::changeClientLocation(unsigned int clientID, int x, int y)
{
	int clientIndex = findClient(clientID);

	//if client not found
	if(clientIndex == -1)
		throw(NotExistentClient(clientID));

	//if client found
	clients.at(clientIndex)->setX(x);
	clients.at(clientIndex)->setY(y);
}
//DONE AND TESTED
void Company::addBike(int x, int y, string bikeType)
{
	int sharePointIndex = findSharePoint(x,y);	//index of SharePoint to add Bike (pointer)

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	if(sharePoints.at(sharePointIndex)->isFull())
		throw FullSharePoint(x,y);	//SharePoint can´t take more bikes

	//if we have all conditions to add bike
	sharePoints.at(sharePointIndex)->addBike(stringToBike(bikeType));

}
//DONE AND TESTED
void Company::removeBike(int x, int y, string bikeType)
{
	int sharePointIndex = findSharePoint(x,y);	//index of SharePoint to add Bike (pointer)

	if(sharePointIndex == -1)	//there isn't a SharePoint at location (x,y)
		throw NotExistentSharePoint(x, y);

	if(!sharePoints.at(sharePointIndex)->removeBike(bikeType))
		throw NotExistentBikeType(bikeType);

}
//DONE AND TESTED
void Company::showClients(string clientType) const
{
	for(size_t i = 0; i < clients.size(); i++)
		if(clients.at(i)->getType() == clientType)
			cout << clients.at(i)->getInformation() << endl;
}
//DONE AND TESTED
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

//DONE AND TESTED
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

//DONE AND TESTED
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
