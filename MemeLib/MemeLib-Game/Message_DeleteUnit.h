#ifndef _MSG_DELETE_UNIT_H_
#define _MSG_DELETE_UNIT_H_

#include "GameMessage.h"

/// <summary>
/// Delete a random unit
/// </summary>
class Message_DeleteUnit : public GameMessage
{
public:
	Message_DeleteUnit();
	~Message_DeleteUnit();

	void process();

private:

};

#endif // !_MSG_CREATE_UNIT_H_
