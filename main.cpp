#include <iostream>
#include <iomanip>
#include <fstream>
#include "bike.h"
#include "sharePoint.h"
#include "company.h"
#include "global.h"
#include "display.h"
#include "piece.h"
#include "workshop.h"
#include "store.h"
#include "date.h"
#include "junkyard.h"

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
	Workshop ws;
	Junkyard jy;

	//get information from file to workshop===================================
	ws.loadBstFromFile();

	//get information from file to junkyard===================================
	jy.loadBrokenBikes();

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



	//reading Stores from file Stores.txt ====================================

	inFile.open("Stores.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'Stores.txt' file" << endl;
		exit(1);
	}

	bikesCompany.readStores(inFile);

	inFile.close();


//=========================================================================
//===========================| MENU |======================================
//=========================================================================
	int option;
	do
	{
		//Main menu has 4 possible options ( from 1 to 8 inclusive )
		displayMainMenu();

		//get the option from the user
		option = getInteger("Choose an option: ",1 , 9);

		switch(option)
		{
		case 1:				//opens the client managemenet menu
		{
			bikesCompany.clientManagementMenu();
			break;
		}
		case 2:				//opens the sharepoint management menu
		{
			bikesCompany.sharePointManagementMenu();
			break;
		}
		case 3:
		{
			bikesCompany.sharePointAnalysisMenu();
			break;
		}
		case 4:				//acts as if it is the end of the month (due to monthly payments by partner clients)
		{
			bikesCompany.endOfMonth();
			break;
		}
		case 5:				//workshop related menu (BINARY SEARCH TREE)
		{
			ws.menu();
			break;
		}
		case 6:				//stores related menu (Priority Queue)
		{
			bikesCompany.storeManagementMenu();
			break;
		}
		case 7:
		{
			jy.menu();
			break;
		}
		case 8:
		{
			bikesCompany.sendBikeToJunkyard(jy);
			break;
		}
		case 9:
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


		//=========================================================================
		//=========================| SAVING INFORMATIONS |=========================
		//=========================================================================

		//saving SharePoints in file "SharePoints.txt"=============================

		ofstream outFile;

		outFile.open("SharePoints.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'SharePoints.txt' file" << endl;
			exit(1);
		}

		bikesCompany.saveSharePoints(outFile);

		outFile.close();

		//saving Clients in file "Clients.txt"====================================

		outFile.open("Clients.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'Clients.txt' file" << endl;
			exit(1);
		}

		bikesCompany.saveClients(outFile);

		outFile.close();

		//save information related to workshop===================================
		ws.saveBstToFile();

		//saving Stores in file "Stores.txt"=====================================

		outFile.open("Stores.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'Stores.txt' file" << endl;
			exit(1);
		}

		bikesCompany.saveStores(outFile);

		outFile.close();

		//save information related to junkyard===================================
		jy.saveBrokenBikes();


	}while(option != 9);
	return 0;
}
