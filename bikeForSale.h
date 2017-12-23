
#ifndef AEDA1_BIKEFORSALE_H_
#define AEDA1_BIKEFORSALE_H_

#include "workshop.h"
#include <iostream>
#include <string>

/**
 * @brief BikeForSale class: a class to create bikes to put in workshop stocks
 */

class BikeForSale {

	private:
		string type;

	public:

		/**
		 * @brief BikeForSale constructor, just creates a bike to add to stock
		 */
		BikeForSale(string t);

		/**
		 * @brief BikeForSale desconstructor
		 */

		~BikeForSaleBikeForSale();


		/**
		 * @return BikeForSale type
		 */

		string getType();
};





#endif /* AEDA1_BIKEFORSALE_H_ */
