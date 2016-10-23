#ifndef _MSG_EXIT_APPLICATION_
#define _MSG_EXIT_APPLICATION_

#include "GameMessage.h"
#include "Vector2.h"

/// <summary>
/// Requests that the game ends at the end of the loop
/// </summary>
class Message_ExitApplication : public GameMessage
{
public:
	Message_ExitApplication();
	~Message_ExitApplication();

	void process();

private:
	Vector2 mPos;
};

#endif // !_MSG_EXIT_APPLICATION_