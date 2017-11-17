#include <iostream>
#include <iomanip>

using namespace std;

void displayMainMenu()
{
	cout << endl;
	cout << "::::::::::::MENU::::::::::::" << endl;
	cout << setw(5) << 1 << ". Client's Management " << endl;
	cout << setw(5) << 2 << ". SharePoint's Management " << endl;
	cout << setw(5) << 3 << ". SharePoint Analysis" << endl;
	cout << setw(5)	<< 4 << ". End of the month " << endl;
	cout << setw(5) << 5 << ". Exit " << endl;
	cout << "::::::::::::::::::::::::::::" << endl << endl;
}

void displayClientManagement()
{
	cout << endl;
	cout << setw(5) << 1 << ". Add Client " << endl;
	cout << setw(5) << 2 << ". Remove Client " << endl;
	cout << setw(5) << 3 << ". Change Client's Location " << endl;
	cout << setw(5) << 4 << ". Pick Bike " << endl;
	cout << setw(5) << 5 << ". Return Bike " << endl;
	cout << setw(5) << 6 << ". Show Partners " << endl;
	cout << setw(5) << 7 << ". Show Regulars " << endl;
	cout << setw(5) << 8 << ". Back to Main Menu" << endl << endl;
}

void displaySharePointManagement()
{
	cout << endl;
	cout << setw(5) << 1 << ". Add SharePoint " << endl;
	cout << setw(5) << 2 << ". Remove SharePoint " << endl;
	cout << setw(5) << 3 << ". Add Bike " << endl;
	cout << setw(5) << 4 << ". Remove Bike " << endl;
	cout << setw(5) << 5 << ". Show SharePoints " << endl;
	cout << setw(5) << 6 << ". Back to Main Menu" << endl << endl;
}

void displaySharePointAnalysis()
{
	cout << endl;
	cout << setw(5) << 1 << ". Bikes Available (Total) " << endl;
	cout << setw(5) << 2 << ". SharePoints ordered by % of occupancy " << endl;
	cout << setw(5) << 3 << ". SharePoints ordered by total number of bikes " << endl;
	cout << setw(5) << 4 << ". Brief Statistic Analysis " << endl;
	cout << setw(5) << 5 << ". Redistribute Bikes " << endl;
	cout << setw(5) << 6 << ". Back to Main Meny " << endl << endl;

}
