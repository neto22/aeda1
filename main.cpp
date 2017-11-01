#include <iostream>
#include <fstream>
#include "bike.h"
#include "sharePoint.h"
#include "company.h"

using namespace std;

int main()
{

	cout << "teste :" << endl;

	Company testCompany;

	//reading SharePoints from file "SharePoints.txt"

	ifstream inFile;

	inFile.open("SharePoints.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'SharePoints' file" << endl;
		exit(1);
	}

	testCompany.readSharePoints(inFile);

	//experimenting

	int num;
	cout << "How many tries to add ? "; cin >> num;

	for(int i = 0; i < num; i++)
	{
		int x, y, capacity;

		cout << "x : "; cin >> x; cout << "y : "; cin >> y; cout << "capacity : "; cin >> capacity;

		try
		{
			testCompany.addSharePoint(new SharePoint(x,y,capacity));
		}

		catch(ExistentSharePoint & e)
		{
			cout << "Location Already Occupied : " << e.getInformation() << endl;
		}
	}

	cout << "number of SharePoints : " << testCompany.getSharePoints().size() << endl;

	cout << "How many tries to remove ? "; cin >> num;
	for(int i = 0; i < num; i++)
	{
		int x, y;

		cout << "x : "; cin >> x; cout << "y : "; cin >> y;

		try
		{
			testCompany.removeSharePoint(x,y);
		}

		catch(NotExistentSharePoint & e)
		{
			cout << "Location doesn't have a SharePoint : " << e.getInformation() << endl;
		}

	}

	cout << "number of SharePoints : " << testCompany.getSharePoints().size() << endl;

	//saving SharePoints in file "SharePoints.txt"

	ofstream outFile;

	outFile.open("SharePoints.txt");

	if(outFile.fail())
	{
		cerr << "Error opening 'SharePoints' file" << endl;
		exit(1);
	}

	testCompany.saveSharePoints(outFile);

	outFile.close();


	return 0;
}
