#ifndef _TRANSACTION_PROCESSOR_H_
#define _TRANSACTION_PROCESSOR_H_

#include <Trackable.h>

//TransactionProcessor class is an abstract base class which mandates a post function - which will do something with a passed in Transaction

struct Transaction;

class TransactionProcessor : public Trackable
{
public:
	void virtual post(const Transaction& theTransaction) = 0;

};

#endif