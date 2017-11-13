#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Asks for a line with a "question" and returns a string with the answer
@param - question associated with the string wanted
*/
string askString(string question);


/*
Asks for a number with "question" and loops until gets a number between min and max
@param - question that the number is associated with
@param - the minimum value accepted
@param - the maximum value accepted
*/
int getInteger(string question, int min, int max);

/*
Asks for a number with "question" and loops until gets a number between min and max
@param - question that the number is associated with
@param - the minimum value accepted
@param - the maximum value accepted
*/
int getDouble(string question, double min, double max);

#endif /* GLOBAL_H_ */
