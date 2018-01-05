#ifndef SRC_WORKSHOP_H_
#define SRC_WORKSHOP_H_

#include "company.h"
#include "BST.h"
#include "piece.h"

/**
 * @brief Class of a Workshop to repair Bike with Piece
 */
class Workshop
{
private:
	BST<Piece> pieces;		/**< Binary Search Tree with all Pieces in Workshop */

public:
	int add(int num);

	//=========================================================================
	//=================| CONSTRUCTORS |===================================
	//=========================================================================
	/**
	 * @brief Constructor of WorkShop
	 */
	Workshop();


	//=========================================================================
	//======================| PRINT |====================================
	//=========================================================================
	/**
	 * @brief Prints information of every Piece in pieces in order
	 * @return void
	 */
	void printAllPieces() const;

	/**
	 * @brief prints the information given as argument
	 * @param piecesToPrint vector of Piece
	 */
	void printVectorPieces(const vector<Piece> &piecesToPrint) const;


	//=========================================================================
	//======================| EDIT |====================================
	//=========================================================================
	/**
	 * @brief Adds new Piece to pieces updating price and quantity or creating a new entry if necessary
	 * @param wanted Piece to be added
	 * @return void
	 */
	void addNewPiece(Piece wanted);

	/**
	 * @brief Takes a vector of Piece as argument and returns it backwards
	 * @param vecPiece - vector of Piece to reverse
	 * @return the backwards vector
	 */
	vector<Piece> reverseVector(vector<Piece> vecPiece);

	//=========================================================================
	//======================| USER OPERATIONS |================================
	//=========================================================================

	/**
	 * @brief Allows user to purchase a new Piece with given name, price and supplier
	 * @return void
	 */
	void purchasePiece();

	/**
	 * @brief Allows user to remove a Piece with given name and supplier
	 * @return void
	 */
	void removePiece();

	/**
	 *  @brief Allows user to find which supplier sold given Piece the cheapest
	 *  @return void
	 */
	void supplierCheapeastPiece();

	/**
	 * @brief Gets from the BST pieces the information wanted by the user (to be defined inside function - associated with a piece name)
	 * @return ordered vector of Piece
	 */
	vector<Piece> infoAboutGivenPiece();

	/**
	 * @brief menu that allows multiple ways of listing pieces
	 * @return void
	 */
	void listingsMenu();

	/**
	 * @brief menu to all workshop related user operations
	 * @return void
	 */
	void menu();
	//=========================================================================
	//================================| FILES |================================
	//=========================================================================

	/**
	 * 	@brief Loads the information in a txt file to the Binary Search Tree pieces
	 * 	@return void
	 */
	void loadBstFromFile(void);

	/**
	 * @brief Takes information in string format and returns a Piece with the same information
	 * @param pieceStr - string with the information needed to create a new Piece
	 * @return Piece with wanted information
	 */
	Piece stringToPiece(string pieceStr);

	/**
	 * @brief Takes information as Piece and returns as a string in order to be saved in a file
	 * @param p1 Piece with information wanted
	 * @return string with information from Piece p1
	 */
	std::string pieceToString(Piece p1);

	/**
	 * @brief Saves the information in a txt file from the Binary Search Tree pieces
	 * @return void
	 */
	void saveBstToFile(void);
};



#endif /* SRC_WORKSHOP_H_ */
