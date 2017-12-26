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

	//get information from file to workshop
	ws.loadBstFromFile();


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
		//Main menu has 4 possible options ( from 1 to 4 inclusive )
		displayMainMenu();

		//get the option from the user
		option = getInteger("Choose an option: ",1 , 7);

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
/*

		vector<Bike *> bikes;

		for(int i = 0; i < 35; i++)
			bikes.push_back(new Urban());
		for(int i = 0; i < 67; i++)
			bikes.push_back(new SimpleUrban());
		for(int i = 0; i < 2;  i++)
			bikes.push_back(new Race());
		for(int i = 0; i < 6; i++)
			bikes.push_back(new Child());

		Store s1("Alvorim das Moscas", bikes);

		cout << s1.storeToString() << endl;

		priority_queue<Store> tmp = bikesCompany.getStores();

		while(!tmp.empty())
		{
			Store s1 = tmp.top();
			tmp.pop();

			cout << s1.storeToString() << endl;
		}

		bikesCompany.removeStore("Campanha");		*/

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


	}while(option != 7);
	return 0;
}
