#ifndef SRC_STORE_H_
#define SRC_STORE_H_

#include "bike.h"
#include <vector>

class Store
{
private:

	string name;
	double reputation;
	vector<Bike *> bikes;
	//vector<int> ratings;
	int totalSumRatings = 0;	//so we can save at file
	int numRatings = 0;			//so we can save at file

public:

	//=========================================================================
	//=================| CONSTRUCTORS |========================================
	//=========================================================================
	/**
	 * @brief Store constructor
	 * @param name Store's name
	 * @param bikes Vector of bikes in stock
	 * @return void
	 */
	Store(string name, vector<Bike *> bikes);	//TOTEST


	//=========================================================================
	//=================| GET FUNCTIONS |=======================================
	//=========================================================================

	/**
	 * @brief Name get function
	 * @return Store's name
	 */
	string getName() const;
	/**
	 * @brief Reputation get function
	 * @return Store's reputation
	 */
	double getReputation() const;
	/**
	 * @brief Bikes get function
	 * @return Store's bikes in stock
	 */
	vector<Bike *> getBikes() const;
	//vector<int> getRatings() const;


	//=========================================================================
	//=================| SET FUNCTIONS |=======================================
	//=========================================================================
	/**
	 *@brief Reputation set function
	 *@param Store's new reputation
	 */
	void setReputation(double reputation);
	/**
	 *@brief Total sum of ratings set function
	 *@param Store's total sum of ratings
	 */
	void setTotalSumRatings(int totalSumRatings);
	/**
	 *@brief Number of ratings set function
	 *@param Store's number of ratings
	 */
	void setNumRatings(int numRatings);



	//=========================================================================
	//=================| CALCULATING FUNCTIONS |===============================
	//=========================================================================
	/**
	 *@brief Calculates number of bikes from a certain type
	 *@param bikeType type of bike
	 *@return number of bikes of given type
	 */
	int bikesInStock(string bikeType) const;	//TOTEST
	/**
	 *@brief function to recalculate the store's reputation
	 */
	void updateReputation();	//TOTEST


	//=========================================================================
	//=================| BOOLEAN FUNCTIONS |===================================
	//=========================================================================
	/**
	 *@brief function to check if the store has the minimum number of bikes of given type
	 *@param bikeType type of bike
	 *@param numBikes number of bikes to buy
	 *@return Returns true if has enough bikes, otherwise returns false
	 */
	bool hasEnoughStock(string bikeType, int numBikes);


	//=========================================================================
	//=================| MANAGEMENT FUNCTIONS |================================
	//=========================================================================
	/**
	 *@brief function to sell bikes, removes them from store
	 *@param bikeType type of bike
	 *@param numBikes number of bikes to buy
	 *@return total price
	 */
	int sellBikes(string bikeType, int numBikes);	//TODO
	/**
	 *@brief function to add a rating
	 *@param rating rating
	 */
	void addRating(int rating);	//TOTEST


	//=========================================================================
	//=================| CONVERT |=============================================
	//=========================================================================
	/**
	 * @brief Converts a Store to a string with the same information, to be able to add it to text files
	 * @return string version of store
	 */
	string storeToString();	//used to save information in file



	//=========================================================================
	//=================| OPERATORS |===========================================
	//=========================================================================
	/**
	 * @brief < overloading, a store is smaller than the other if the reputation is smaller
	 * @return Returns true is smaller, otherwise returns false
	 */
	bool operator<(const Store & s2) const;


};


//=========================================================================
//=================| PRINT |===============================================
//=========================================================================
/**
 * @brief << overloading, turns a store to a stringstream
 * @return stringstream that represents the store
 */
ostream& operator<<(ostream& os, const Store & s1);


#endif
