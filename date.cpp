#include "date.h"

#include <iostream>

using namespace std;

//=========================================================================
//=================| CONSTRUCTORS |========================================
//=========================================================================

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

//=========================================================================
//=================| GET |=================================================
//=========================================================================
unsigned int Date::getDay() const
{
	return day;
}

unsigned int Date::getMonth() const
{
	return month;
}

unsigned int Date::getYear() const
{
	return year;
}

string Date::getInformation() const
{
	return to_string(day) + " , " + to_string(month) + " , " + to_string(year);
}

//=========================================================================
//=================| OPERATORS |===========================================
//=========================================================================

bool Date::operator < (Date & d2) const
{
	if(year == d2.year)
	{
		if(month == d2.month)
			return day < d2.day;

		return month < d2.month;
	}

	return year < d2.year;
}

bool  Date::operator == (Date & d2) const
{
	return ( (year == d2.year) && (month == d2.month) && (day == d2.day));
}

ostream & operator << (ostream & os, const Date & d1)
{
	os << std::to_string(d1.getDay()) << "/" << std::to_string(d1.getMonth()) << "/" << std::to_string(d1.getYear());

	return os;
}
