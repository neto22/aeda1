#include "workshop.h"
#include "piece.h"
#include "global.h"
#include "display.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//=========================================================================
//=================| CONSTRUCTORS |===================================
//=========================================================================

Workshop::Workshop(): pieces(Piece("","",0,0))
{
	//DO NOTHING
}

string Workshop::getName() {
	return name;
}

float Workshop::getReputation() {
	return reputation;
}

vector<int> Workshop::getRatings() {
	return ratings;
}

vector<BikeForSale *> Workshop::getBikes() {
	return bikes;
}


void Workshop::pushRating(int rating) {
	ratings.push_back(rating);
	calcReputation();
}


//=========================================================================
//======================| PRINT |====================================
//=========================================================================

void Workshop::printAllPieces() const
{
	BSTItrIn<Piece> it(pieces);

	if(pieces.isEmpty())
		return;

	while(!it.isAtEnd())
	{
		cout << "=============" << endl;
		cout << it.retrieve();

		it.advance();
	}
}

void Workshop::printVectorPieces(const vector<Piece> &piecesToPrint) const
{
	for(unsigned int i = 0 ; i < piecesToPrint.size();i++)
	{
		cout << "=====================" << endl;
		cout << piecesToPrint.at(i) << endl;
	}
}

//=========================================================================
//======================| EDIT |===========================================
//=========================================================================

void Workshop::addNewPiece(Piece wanted)
{
	//local variables
	Piece notFound("","",0,0);
	Piece findAttempt = pieces.find(wanted);

	//check if the piece is already there
	if(!(findAttempt == notFound))
	{
		//found a piece with same name price and supplier
		unsigned int quant = findAttempt.getQuantity() + wanted.getQuantity();
		unsigned int lastPrice = wanted.getPrice();

		Piece newPiece(wanted.getName(), wanted.getSupplier(), lastPrice, quant);
		pieces.remove(findAttempt);
		pieces.insert(newPiece);
		return;
	}
	else
	{
		//didnt find the piece, but can have same name and supplier but different price
		BSTItrIn<Piece> it(pieces);
		while(!it.isAtEnd())
		{
			Piece current = it.retrieve();
			if(current == wanted)
			{
				//found with same name and supplier, means it has to update price and add quanity
				Piece newPiece(wanted.getName(), wanted.getSupplier(), wanted.getPrice(), current.getQuantity() + wanted.getQuantity());
				pieces.remove(current);
				pieces.insert(newPiece);
				return;
			}
			it.advance();
		}

		//if it reaches this point, it means it doesnt have name and supplier in common
		pieces.insert(wanted);
	}
}

vector<Piece> Workshop::reverseVector(vector<Piece> vecPiece)
{
	vector<Piece> result;

	for(int i = vecPiece.size()-1; i >= 0;i--)
	{
		result.push_back(vecPiece.at(i));
	}
	return result;
}

//=========================================================================
//======================| USER OPERATIONS |================================
//=========================================================================

void Workshop::listingsMenu()
{
	string mode;
	do
	{
		mode = askString("Mode of listing (total/parcial)");
	}while(mode != "total" && mode != "parcial");

	if(mode == "total")
	{
		//total listings
		cout << "1. By Name, Price and Supplier (crescent)" << endl;
		cout << "2. By Name, Price and Supplier (decrescent)" << endl;
		int option = getInteger("Option: ",1,2);

		vector<Piece> vecPiece;
		BSTItrIn<Piece> it(pieces);

		while(!(it.isAtEnd()))
		{
			Piece curr = it.retrieve();

			vecPiece.push_back(curr);
			it.advance();
		}

		switch(option)
		{
		case 1:
		{
			printVectorPieces(vecPiece);
			break;
		}
		case 2:
		{
			//BST backwards
			vecPiece = reverseVector(vecPiece);
			printVectorPieces(vecPiece);
			break;
		}
		}
	}
	else
	{
		//parcial listings
		cout << "1. All pieces with given name by price (crescent)" << endl;
		cout << "2. All pieces with given name by price (decrescent)" << endl;
		int option = getInteger("Option:",1,2);

		if(option == 1)
		{
			//crescent
			vector<Piece> wanted = infoAboutGivenPiece();
			printVectorPieces(wanted);
		}
		else
		{
			//Decrescent
			vector<Piece> wanted = infoAboutGivenPiece();
			wanted = reverseVector(wanted);
			printVectorPieces(wanted);
		}
	}
}

void Workshop::purchasePiece()
{
	//get the new values
	string pieceName = askString("Name: ");
	string pieceSupplier = askString("Supplier: ");
	unsigned int price = getInteger("Price of one unit: ",0,99999);
	unsigned int quantity = getInteger("How many units? ", 1, 99999);

	Piece newPiece(pieceName,pieceSupplier,price,quantity);
	addNewPiece(newPiece);

	cout << "Purchase Successful" << endl << endl;
}

void Workshop::removePiece()
{
	//get the new values
	string pieceName = askString("Name: ");
	string pieceSupplier = askString("Supplier: ");
	unsigned int quantity = getInteger("How many units? ", 1, 99999);

	BSTItrIn<Piece> it(pieces);
	Piece comp(pieceName,pieceSupplier,0,0);

	while(!(it.isAtEnd()))
	{
		Piece currentPiece = it.retrieve();

		if(currentPiece == comp)
		{
			//check if its possible to remove quantity amount of units
			unsigned int quantAvailable = currentPiece.getQuantity();

			if(quantAvailable <= quantity)
			{
				//cant remove all quantity units
				cout << "All the stock were removed and therefore the registry was deleted"	 << endl;

				pieces.remove(currentPiece);
				return;
			}
			else
			{
				Piece newPiece(currentPiece.getName(), currentPiece.getSupplier(), currentPiece.getPrice(), quantAvailable - quantity);
				cout << quantity << "/" << quantAvailable << " removed successfully" << endl;

				pieces.remove(currentPiece);
				addNewPiece(newPiece);
				return;
			}
		}
		it.advance();
	}

	//if it reaches here, not found
	cout << "No such registry found with those specifications" << endl;

	//TODO - se chegar aqui quer dizer que nao existe registo nenhum com o mesmo nome e com o mesmo fornecedor por isso podes lan�ar a exce�ao em vez da mensagem que tenho
}

void Workshop::supplierCheapeastPiece()
{
	//local variables
	string pieceName = askString("Name: ");		//name of piece
	unsigned int min = 999;						//price of cheapest piece so far
	string supplier;

	if(pieces.isEmpty())
	{
		cout << "No Available Piece" << endl;
		return;
	}

	BSTItrIn<Piece> it(pieces);
	while(!(it.isAtEnd()))
	{
		Piece currentPiece = it.retrieve();

		if(currentPiece.getName() == pieceName)
		{
			if(currentPiece.getPrice() < min)
			{
				min = currentPiece.getPrice();
				supplier = currentPiece.getSupplier();
			}

		}
		it.advance();
	}

	//already went through all the values
	cout << "The supplier that sold " << pieceName << " the cheapest was " << supplier << " at " << min << " euros per unit" << endl;
}

vector<Piece> Workshop::infoAboutGivenPiece()
{
	//get the new values
	string pieceName = askString("Name: ");

	vector<Piece> result;
	BSTItrIn<Piece>	it(pieces);
	bool foundOne = false;

	while(!(it.isAtEnd()))
	{
		Piece currentPiece = it.retrieve();

		if(pieceName == currentPiece.getName())
		{
			foundOne = true;
			result.push_back(currentPiece);
		}
		else
		{
			//BST is ordered by name, if it found one already but not anymore it means there wont be any more with the same name
			if(foundOne)
				return result;
		}

		it.advance();
	}
	if(result.size()==0)
	{
		cout << "not any piece with those specifications" << endl;
		return result;
	}
	else
		return result;
}

void Workshop::menu()
{
	displayWorkshopMenu();
	int option = getInteger("Option: ",1,5);

	switch(option)
	{
	case 1:					//purchase pieces
	{
		purchasePiece();
		break;
	}
	case 2:					//look for cheapest piece
	{
		supplierCheapeastPiece();
		break;
	}
	case 3:					//remove
	{
		removePiece();
		break;
	}
	case 4:					//multiple listings
	{
		listingsMenu();
		break;
	}
	case 5:					//return to main menu
	{
		cout << "Leaving Workshop Menu" << endl;
		break;
	}
	default:
	{
		//get integer prevents it from reaching default
	}
	}
}

//=========================================================================
//================================| FILES |================================
//=========================================================================

Piece Workshop::stringToPiece(string pieceStr)
{
	char next;
	string name, supplier, trash;
	unsigned int price, quantity;

	istringstream iStr(pieceStr);

	while(next != ';')
	{
		name += next;
		iStr.get(next);
	}
	name = name.substr(1, name.length() - 2); //removes spaces

	next = 0;

	while(next != ';')
	{
		supplier += next;
		iStr.get(next);
	}
	supplier = supplier.substr(2,supplier.length()-3);

	iStr >> price >> trash >> quantity;

	Piece currentPiece(name,supplier,price,quantity);
	return currentPiece;
}

string Workshop::pieceToString(Piece p1)
{
	string res = p1.getName() + " ; " + p1.getSupplier() + " ; " + to_string(p1.getPrice()) + " ; " + to_string(p1.getQuantity());
	return res;
}

void Workshop::loadBstFromFile(void)
{
	ifstream inFile;
	inFile.open("Pieces.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'Pieces.txt' file" << endl;
		exit(1);
	}

	while(!inFile.eof())
	{
		string piece;
		getline(inFile,piece);

		Piece currentPiece = stringToPiece(piece);
		addNewPiece(currentPiece);
	}

}

void Workshop::saveBstToFile(void)
{
	BSTItrIn<Piece> it(pieces);

	ofstream outFile;
	outFile.open("Pieces.txt");

	if(outFile.fail())
	{
		cerr << "Error opening 'Pieces.txt' file" << endl;
		exit(1);
	}

	//save first element
	outFile << pieceToString(it.retrieve());

	it.advance();

	while(!(it.isAtEnd()))
	{
		Piece currentPiece = it.retrieve();
		string str = pieceToString(currentPiece);

		outFile << endl << str;

		it.advance();
	}
}


bool Workshop::operator<(const Workshop & w) const
{
	return reputation < w.reputation;
}

int Workshop::bikesInStock (string type) {

	int total;

	for (int i = 0; i < bikes.size(); i++) {
		if (bikes[i]->getType() == type) {
			total++;
		}
	}

	return total;
}

void Workshop::calcReputation() {

	float r = 0;

	for (int i = 0; i < ratings.size(); i++) {
		r += ratings[i];
	}

	r /= ratings.size();

	reputation = r;
}

void Workshop::sellBikes(string type, int n) {
	int rem = 0;
	int i = 0;

	while ((rem < n) && (i < bikes.size())) {
		if (bikes[i]->getType() == type) {
			bikes.erase(bikes.begin()+i);
			rem++;
		} else {
			i++;
		}
	}
}
