#include "junkyard.h"

#include "company.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

//====================================================================================
//=================| BROKENBIKE |=====================================================
//====================================================================================
unsigned int Bike::bikeID = 1;

//=========================================================================
//=================| CONSTRUCTORS |========================================
//=========================================================================
BrokenBike::BrokenBike(Bike * b1)
{
	bike = b1;
	b1->setID(Bike::bikeID);
	Bike::bikeID++;
}

//=========================================================================
//=================| GET |=================================================
//=========================================================================
Bike * BrokenBike::getBike() const
{
	return bike;
}

Date BrokenBike::getDate() const
{
	return date;
}

//=========================================================================
//=================| SET |=================================================
//=========================================================================
void BrokenBike::setDate(Date newDate)
{
	date = newDate;
}

//=========================================================================
//=================| BOOLEAN |=============================================
//=========================================================================
bool BrokenBike::wrecked() const
{
	return (date.getDay() != 0) && (date.getMonth() != 0) && (date.getYear() != 0);
}



//====================================================================================
//=================| JUNKYARD |=======================================================
//====================================================================================

//=========================================================================
//=================| CONSTRUCTORS |========================================
//=========================================================================
Junkyard::Junkyard()
{

}

//=========================================================================
//======================| EDIT |===========================================
//=========================================================================

void Junkyard::addBike(Bike * b1)
{
	BrokenBike bb1(b1);

	brokenBikes.insert(bb1);
}

void Junkyard::wreckBike(unsigned int id, const Date & d1)
{
	unsigned int lastID = Bike::bikeID;		//saving last ID, because creating BrokenBikes will change it

	Bike * bike = new Bike();
	BrokenBike toFind(bike);
	toFind.getBike()->setID(id);	//to check if there is already a bike with id in the HashTable
	Bike::bikeID = lastID;

	HashTable::iterator findAttempt;

	findAttempt = brokenBikes.find(toFind);

	if(findAttempt == brokenBikes.end())
		throw NotExistentBike(id);

	BrokenBike tmp = *findAttempt;
	brokenBikes.erase(findAttempt);
	tmp.setDate(d1);
	brokenBikes.insert(tmp);

}

void Junkyard::removeBike(unsigned int id)
{
	unsigned int lastID = Bike::bikeID;		//saving last ID, because creating BrokenBikes will change it

	Bike * bike = new Bike();
	BrokenBike toFind(bike);
	toFind.getBike()->setID(id);	//to check if there is already a bike with id in the HashTable
	Bike::bikeID = lastID;

	HashTable::iterator findAttempt;

	findAttempt = brokenBikes.find(toFind);

	//if there isn't a bike with such id
	if(findAttempt == brokenBikes.end())
		throw NotExistentBike(id);

	//if bike is found but it was not wrecked yet, it can't be removed
	if(!findAttempt->wrecked())
		throw NotWreckedBike(id);

	//if bike already exists and already was wrecked, it can be removed
	brokenBikes.erase(findAttempt);

}

void Junkyard::cleanJunkyard()
{
	HashTable tmp;
	HashTable::iterator it;

	if(brokenBikes.empty())
		return;

	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if(!it->wrecked())	//bike was not wrecked yet (save it)
			tmp.insert(*it);
	}

	//tmp has all not wrecked bikes, so we swap it contents with the brokenBikes, so the brokenBikes lose all wrecked bikes
	swap(brokenBikes, tmp);

}

//=========================================================================
//======================| PRINT |==========================================
//=========================================================================
void Junkyard::showAllBikes()
{
	HashTable::iterator it;

	cout << "Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		cout << "::::::::::::::::::::::::::::::" << endl;
		cout << *it << endl;
	}
}

void Junkyard::showWreckedBikes()
{
	HashTable::iterator it;

	cout << "Wrecked Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if(it->wrecked())
		{
			cout << "::::::::::::::::::::::::::::::" << endl;
			cout << *it << endl;
		}
	}
}

void Junkyard::showNotWreckedBikes()
{
	HashTable::iterator it;

	cout << "Not Wrecked Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if(!it->wrecked())
		{
			cout << "::::::::::::::::::::::::::::::" << endl;
			cout << *it << endl;
		}
	}
}

void Junkyard::showTypeBikes(string bikeType)
{
	HashTable::iterator it;

	cout << bikeType << " Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if(it->getBike()->getType() == bikeType)
		{
			cout << "::::::::::::::::::::::::::::::" << endl;
			cout << *it << endl;
		}
	}
}

void Junkyard::showWreckedTypeBikes(string bikeType)
{
	HashTable::iterator it;

	cout << bikeType << " Wrecked Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if((it->getBike()->getType() == bikeType) && it->wrecked())
		{
			cout << "::::::::::::::::::::::::::::::" << endl;
			cout << *it << endl;
		}
	}
}

void Junkyard::showNotWreckedTypeBikes(string bikeType)
{
	HashTable::iterator it;

	cout << bikeType << " Wrecked Bikes at Junkyard: " << endl << endl;
	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if((it->getBike()->getType() == bikeType) && (!it->wrecked()))
		{
			cout << "::::::::::::::::::::::::::::::" << endl;
			cout << *it << endl;
		}
	}
}


//=========================================================================
//======================| USER OPERATIONS |================================
//=========================================================================

void Junkyard::userWreckBike()
{
	unsigned int id, day, month, year;	//information that user will give

	id = getInteger("Bike's ID: ",0,99999);
	cout << "Last Wreck at: " << lastDate << " (not allowed dates before that)" << endl;
	do
	{
		day = getInteger("Day of the month: ", 0, 31);
		month = getInteger("Month: ",0, 12);
		year = getInteger("Year: ", 2000, 4000);

	}while(Date(day,month, year) < lastDate);

	try
	{
		wreckBike(id, Date(day, month, year));

		//if bike was wrecked successfuly
		lastDate = Date(day,month,year);
	}

	catch(NotExistentBike & e)
	{
		cout << "There isn't a Bike to wreck with id :" << e.getID();
	}
}


void Junkyard::userRemoveBike()
{
	unsigned int id = getInteger("Bike's ID: ",0,99999);

	try
	{
		removeBike(id);
	}

	catch(NotExistentBike & e)
	{
		cout << "There isn't a Bike to wreck with id :" << e.getID();
	}
	catch(NotWreckedBike & e)
	{
		cout << "Bike with id " << e.getID() << " wasn't wrecked yet. Please wreck it before remove it! " << endl;
	}

}

void Junkyard::listingsMenu()
{
	cout << ":::Partial Listing of Broken Bikes:::" << endl;
	cout << "1. Wrecked " << endl;
	cout << "2. Waiting to be Wrecked " << endl;
	cout << "3. By Type" << endl;
	cout << "4. By Type and Wrecked " << endl;
	cout << "5. By Type and Not Wrecked " << endl;

	int option = getInteger("Option: ",1,5);

	string bikeType;
	if(option != 1 && option != 2)
	{
		do
		{
		bikeType = askString("Bike Type (Urban/SimpleUrban/Race/Child): ");

		}while((bikeType != "Urban") && (bikeType != "SimpleUrban") && (bikeType != "Race") && (bikeType != "Child"));

	}

	switch(option)
	{
	case 1:
	{
		showWreckedBikes();
		break;
	}
	case 2:
	{
		showNotWreckedBikes();
		break;
	}
	case 3:
	{
		showTypeBikes(bikeType);
		break;
	}
	case 4:
	{
		showWreckedTypeBikes(bikeType);
		break;
	}
	case 5:
	{
		showNotWreckedTypeBikes(bikeType);
		break;
	}
	default:
	{
		//it doesn't reach here
	}

	}

}

void Junkyard::menu()
{
	displayJunkyardMenu();
	int option = getInteger("Option: ",1,6);

	switch(option)
	{
	case 1:
	{
		userWreckBike();
		break;
	}
	case 2:
	{
		userRemoveBike();
		break;
	}
	case 3:
	{
		showAllBikes();
		break;
	}
	case 4:
	{
		listingsMenu();
		break;
	}
	case 5:
	{
		cleanJunkyard();
		break;
	}
	case 6:
	{
		cout << "Leaving Junkyard Menu" << endl;
		break;
	}
	default:
	{

	}

	}
}


//=========================================================================
//================================| FILES |================================
//=========================================================================
void Junkyard::loadBrokenBikes()
{
	string bb1;
	unsigned int maxID =  0;

	ifstream inFile;
	inFile.open("BrokenBikes.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'BrokenBikes.txt' file" << endl;
		exit(1);
	}

	while(!inFile.eof())
	{
		getline(inFile, bb1);
		BrokenBike current = stringToBrokenBike(bb1);

		//update Bike::id
		if(maxID < current.getBike()->getID())
			maxID = current.getBike()->getID();

		//saves BrokenBike obtained with convertion at brokenBikes HasthTable
		brokenBikes.insert(stringToBrokenBike(bb1));
	}

	Bike::bikeID = maxID + 1;

	cout << Bike::bikeID << endl;

	inFile.close();
}

string Junkyard::brokenBikeToString(BrokenBike bb1)
{
	string res;

	res = to_string(bb1.getBike()->getID()) + " ; " + bb1.getBike()->getType() + " ; " + bb1.getDate().getInformation();

	return res;
}

BrokenBike Junkyard::stringToBrokenBike(string bb1)
{
	istringstream iStr(bb1);
	string type, irrelevant;
	unsigned int id, day, month, year;

	iStr >> id >> irrelevant >> type >> irrelevant >> day >> irrelevant >> month >> irrelevant >>year;

	Bike * b1 = stringToBike(type);
	BrokenBike converted(b1);
	converted.getBike()->setID(id);
	converted.setDate(Date(day,month,year));

	return converted;
}

Bike * Junkyard::stringToBike(string b1)
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

void Junkyard::saveBrokenBikes()
{
	HashTable::iterator it;

	ofstream outFile;
	outFile.open("BrokenBikes.txt");

	if(outFile.fail())
	{
		cerr << "Error opening 'BrokenBikes.txt' file" << endl;
		exit(1);
	}

	for(it = brokenBikes.begin(); it != brokenBikes.end(); it++)
	{
		if(it != brokenBikes.begin())
			outFile << endl;

		outFile << brokenBikeToString(*it);
	}

	outFile.close();
}

void Junkyard::readLastWreckDate()
{
	ifstream inFile;
	inFile.open("lastDate.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'lastDate.txt' file" << endl;
		exit(1);
	}

	string date, irrelevant;
	unsigned int day, month, year;

	getline(inFile, date);
	istringstream iStr(date);

	iStr >> day >> irrelevant >> month >>irrelevant >> year;

	lastDate = Date(day, month, year);
}


void Junkyard::saveLastWreckDate()
{
	ofstream outFile;
	outFile.open("lastDate.txt");

	if(outFile.fail())
	{
		cerr << "Error opening 'lastDate.txt' file" << endl;
		exit(1);
	}

	outFile << lastDate.getInformation();
	outFile.close();
}


//=========================================================================
//================================| OPERATORS |============================
//=========================================================================
ostream & operator<<(ostream& os, const BrokenBike & b1)
{
	os << "ID:   " << b1.getBike()->getID() << endl;
	os << "Type: " << b1.getBike()->getType() << endl;
	os << "Date: ";
	if(b1.wrecked())
		os << b1.getDate();
	else
		os << "Not wrecked yet" << endl;

	return os;
}
