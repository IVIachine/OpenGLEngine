#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <Trackable.h>
#include "Vector2.h"

enum TransactionType
{
	INVALID_TRANSACTION_TYPE = -1,
	POSITION_TRANSACTION,
	PHYSICS_TRANSACTION
};

//Transactions are how COMPONENT_MANAGER modify TransactionProcessors

struct Transaction : public Trackable
{
	Transaction(TransactionType theType) :type(theType) {};

	TransactionType type;
};

struct PositionTransaction : public Transaction
{
	PositionTransaction(const Vector2& thePosMod, float theFacingMod) :Transaction(POSITION_TRANSACTION), posMod(thePosMod), facingMod(theFacingMod) {};
	PositionTransaction() :Transaction(POSITION_TRANSACTION), posMod(Vector2::ZERO), facingMod(0.0f) {};

	Vector2 posMod;//how much do we change the position
	float facingMod;//how much do we rotate
};

#endif