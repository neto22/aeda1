#include "workshop.h"
#include "piece.h"
#include "global.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Workshop::Workshop(): pieces(Piece("","",0,0))
{
	//DO NOTHING
}

int main()
{
	Workshop ws;

	ws.add(2);

}

int Workshop::add(int num)
{
	loadBstFromFile();
	printAllPieces();

	removePiece();




	saveBstToFile();

	return 0;
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

//=========================================================================
//======================| EDIT |====================================
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

//=========================================================================
//======================| USER OPERATIONS |====================================
//=========================================================================

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
				cout << quantity << "/" << quantAvailable << "removed successfully" << endl;

				pieces.remove(currentPiece);
				addNewPiece(newPiece);
				return;
			}
		}
		it.advance();
	}

	//if it reaches here, not found
	cout << "No such registry found with those specifications" << endl;
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


