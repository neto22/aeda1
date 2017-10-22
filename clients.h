#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "ap.h"
#include "bike.h"

class Client {
	public:
		int addClient(unsigned int type);
		virtual double pay();

	protected:
		unsigned int user_id;
		string name;
		static int id_counter;
		Bike currentBike;
};
class Partner: public Client {
	public:
		double pay();
};
class Regular: public Client {
	public:
		double pay();
};


#endif
