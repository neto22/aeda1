#include <iostream>
#include <iomanip>
#include <fstream>
#include "bike.h"
#include "sharePoint.h"
#include "company.h"
#include "global.h"
#include "display.h"

using namespace std;

string askString(string question)
{
	//local variable
	string answer;

	cout << question;
	getline(cin, answer);

	return answer;
}

int getInteger(string question, int min, int max)
{
	//local variables
	bool error = false;
	int option;

	do
	{
		option = 0;
		do
		{
			cout << question;
			if (error == true)
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin >> option;
			error = true;

		} while (cin.fail());
		error = false;

	} while (!(option >= min && option <= max));

	cin.ignore(1000, '\n');
	return option;
}

int getDouble(string question, double min, double max)
{
	//local variables
	bool error = false;
	double option;

	do
	{
		option = 0;
		do
		{
			cout << question;
			if (error == true)
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin >> option;
			error = true;

		} while (cin.fail());
		error = false;

	} while (!(option >= min && option <= max));

	cin.ignore(1000, '\n');
	return option;
}

int main()
{

	/*GETTING SAVED INFORMATION FROM FILES*/

	Company bikesCompany;

	//reading SharePoints from file "SharePoints.txt" ========================

	ifstream inFile;

	inFile.open("SharePoints.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'SharePoints.txt' file" << endl;
		exit(1);
	}

	bikesCompany.readSharePoints(inFile);

	inFile.close();



	//reading Clients from file "Clients.txt" =================================

	inFile.open("Clients.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'Clients.txt' file" << endl;
		exit(1);
	}

	bikesCompany.readClients(inFile);

	inFile.close();


//=========================================================================
//===========================| MENU |======================================
//=========================================================================
	int option;
	do
	{
		//Main menu has 3 possible options ( from 1 to 3 inclusive )
		displayMainMenu();

		//get the option from the user
		option = getInteger("Choose an option: ",1 , 3);

		switch(option)
		{
		case 1:
		{
			bikesCompany.clientManagementMenu();
			break;
		}
		case 2:
		{
			bikesCompany.sharePointManagementMenu();
			break;
		}
		case 3:
		{
			cout << "End of program"<< endl;
			break;
		}
		default:
		{
			//it never gets to default since the menu option is delimited by getInteger()
			break;
		}
		}


		//=========================================================================
		//===============================| TESTING  |==============================
		//=========================================================================

		/*other tests: to remove later

		cout << "number of SharePoints : " << bikesCompany.getSharePoints().size() << endl;

		cout << "number of Clients  : " << bikesCompany.getClients().size() << endl;

		//closest SharePoint
		int clientInd;
		cout << "Client index to find closest SharePoint to return bike: "; cin >>clientInd;

		try
		{
			SharePoint * p1 = bikesCompany.getClients().at(clientInd)->closestSHtoReturn(bikesCompany.getSharePoints());
			cout << "Closest SharePoint : "<< *p1 << endl;
		}

		catch(NotAvaibleSharePoints & e)
		{
			cout << "Not Avaible SharePoints" << endl;
		}

		string bikeType;
		cout << "Client index to find closest SharePoint to peek bike: "; cin >> clientInd;
		cout << "Bike Type : "; cin >> bikeType;

		try
		{
			SharePoint * p1 = bikesCompany.getClients().at(clientInd)->closestSHtoPeek(bikesCompany.getSharePoints(), bikeType);
			cout << "Closest SharePoint : "<< *p1 << endl;
		}

		catch(NotAvaibleSharePoints & e)
		{
			cout << "Not Avaible SharePoints with : " << e.getBykeType() <<  endl;
		}
		 */

		//=========================================================================
		//=========================| SAVING INFORMATIONS |=========================
		//=========================================================================

		//saving SharePoints in file "SharePoints.txt"

		ofstream outFile;

		outFile.open("SharePoints.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'SharePoints' file" << endl;
			exit(1);
		}

		bikesCompany.saveSharePoints(outFile);

		outFile.close();

		//saving Clients in file "Clients.txt"

		outFile.open("Clients.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'SharePoints' file" << endl;
			exit(1);
		}

		bikesCompany.saveClients(outFile);

		outFile.close();

	}while(option != 3);
}
