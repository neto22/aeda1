#ifndef SRC_PIECE_H_
#define SRC_PIECE_H_

#include <string>
#include <sstream>

/**
 * @brief Registry of a Piece for a Binary Search Tree
 */
class Piece
{
private:

	std::string name;		/**< name of Piece */
	std::string supplier;	/**< supplier of Piece */
	unsigned int price;		/**< price of a unit of Piece */
	unsigned int quantity;	/**< quantity of Piece in registry */

public:

	//=========================================================================
	//=================| OPERATORS |===========================================
	//=========================================================================
	/**
	 * @brief Piece Constructor
	 * @param name Designation of the Piece
	 * @param supplier Supplier of the Piece
	 * @param price Price of a unit of type Piece
	 * @param quantity Amount of units of type Piece
	 */
	Piece(std::string name, std::string supplier, unsigned int price, unsigned int quantity);
	/**
	 * @brief Piece Constructor
	 * @param name Designation of the Piece
	 * @param supplier Supplier of the Piece
	 * @param price Price of a unit of type Piece
	 */
	Piece(std::string name, std::string supplier, unsigned int price);

	//=========================================================================
	//=================| GET FUNCTIONS |=======================================
	//=========================================================================
	/**
	 * @return name of Piece
	 */
	std::string getName() const;
	/**
	 * @return supplier of Piece
	 */
	std::string getSupplier() const;
	/**
	 * @return quantity of Piece
	 */
	unsigned int getQuantity() const;
	/**
	 * @return price of a unit of Piece
	 */
	unsigned int getPrice() const;

	//=========================================================================
	//=================| OPERATORS |===========================================
	//=========================================================================
	/**
	 * @brief Checks if Piece p1 is smaller than object by name, price and supplier
	 * @param p1 Piece to be compared with
	 * @return true if Piece p1 is larger, false if Piece p1 is smaller
	 */
	bool operator<(const Piece &p1) const;
	/**
	 * @brief Checks if Piece p1 is equal to an object by name and supplier
	 * @param p1 Piece to be compared with
	 * @return true if Piece p1 is equal, false otherwise
	 */
	bool operator==(const Piece &p1) const;
	/**
	 * @brief Organizes information of Piece p in a out stream
	 * @param os ostream which will be updated with Piece p information
	 * @param p Piece p
	 * @return ostream os with the information from Piece p
	 */
	friend std::ostream & operator<<(std::ostream& os, const Piece& p);
};



#endif /* SRC_PIECE_H_ */
