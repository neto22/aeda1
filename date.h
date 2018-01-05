#ifndef SRC_DATE_H_
#define SRC_DATE_H_

#include <string>

class Date
{
private:
	unsigned int day, month, year;

public:

	//=========================================================================
	//=================| CONSTRUCTORS |========================================
	//=========================================================================
	/**
	 * @brief Constructor of Date without parameters
	 *  It initialazes object with 0/0/0 (day/month/year), this means date is not being used  yet
	 */
	Date();

	/**
	 * @brief Constructor of Date
	 * @param day Integer with day
	 * @param month Integer with month
	 * @param year Integer with year
	 */
	Date(unsigned int day, unsigned int month, unsigned int year);


	//=========================================================================
	//=================| GET |=================================================
	//=========================================================================
	/**
	 * @brief Returns date's day
	 * @return Returns day
	 */
	unsigned int getDay() const;

	/**
	 * @brief Returns date's month
	 * @return Returns month
	 */
	unsigned int getMonth() const;

	/**
	 * @brief Returns date's year
	 * @return Returns year
	 */
	unsigned int getYear() const;

	/**
	 * @brief Returns date's information as a string to be saved in a txt file
	 * @return Dates's information as a string to be saved in a txt file
	 */
	std::string getInformation() const;

	//=========================================================================
	//=================| OPERATORS |===========================================
	//=========================================================================
	/**
	 * @brief Checks if date object is before date2
	 * @param d2 Date to be compared with
	 * @return true if date is prior to d2, false otherwise
	 */
	bool operator < (Date & d2) const;

	/**
	 * @brief Checks if date is equal to date2
	 * @param d2
	 * @return true if date is equal to d2, false otherwise
	 */
	bool operator == (Date & d2) const;

};

std::ostream & operator << (std::ostream & os, const Date & d1);

#endif
