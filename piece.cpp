#include "piece.h"
#include "workshop.h"

#include <iostream>

using namespace std;

//=========================================================================
//=================| CONSTRUCTORS |===================================
//=========================================================================

Piece::Piece(string name,string supplier,unsigned int price,unsigned int quantity)
{
	this->name = name;
	this->supplier = supplier;
	this->price = price;
	this->quantity = quantity;
}

Piece::Piece(string name, string supplier, unsigned int price)
{
	this->name = name;
	this->supplier = supplier;
	this->price = price;
	this->quantity = 1;
}

//=========================================================================
//=================| GET FUNCTIONS |===================================
//=========================================================================

string Piece::getName() const
{
	return name;
}

string Piece::getSupplier() const
{
	return supplier;
}

unsigned int Piece::getQuantity() const
{
	return quantity;
}

unsigned int Piece::getPrice() const
{
	return price;
}



//=========================================================================
//=================| OPERATORS |===================================
//=========================================================================

bool Piece::operator <(const Piece &p1) const
{
	//order by name,price and supplier
	if((getName() == p1.getName()) && (getPrice() == p1.getPrice()))
	{
		return (getSupplier() < p1.getSupplier());
	}
	else if(getName() == p1.getName())
	{
		return (getPrice() < p1.getPrice());
	}
	else
	{
		return (getName() < p1.getName());
	}

}

bool Piece::operator ==(const Piece &p1) const
{
	if((getSupplier() == p1.getSupplier())&&(getName() == p1.getName()))
		return true;
	else
		return false;
}

ostream& operator<<(ostream& os, const Piece& p)
{
	os      << "Name:     " << p.getName() << endl
			<< "Price:    " << p.getPrice() << endl
			<< "Supplier: " << p.getSupplier() << endl
			<< "Quantity: " << p.getQuantity() << endl;

	return os;
}

