#ifndef _GAME_MESSAGE_H_
#define _GAME_MESSAGE_H_

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	MSG_PLAYER_MOVE_TO = 0,
	MSG_EXIT_APPLICATION,
	MSG_CREATE_UNIT,
	MSG_DELETE_UNIT,
	MSG_UPDATE_FLOCKING
};

class GameMessage : public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage(MessageType type);
	~GameMessage();

	float getSubmittedTime() const { return mSubmittedTime; };
	float getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	float mSubmittedTime;
	float mScheduledTime;

private:
	virtual void process() = 0;
};

#endif