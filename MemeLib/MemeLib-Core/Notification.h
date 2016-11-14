#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include <Trackable.h>

//Notifications are messages that are intended to be queued up for later processing
//     They contain callback functions which will actually handle the Notification when it is time to process them


class Notification;
class NotificationQueue;

typedef void(*NotificationCallback)(Notification*);

class Notification :public Trackable
{
	friend class NotificationQueue;
public:
	Notification() { m_id = msID++; };
	inline unsigned int getID() { return m_id; };
private:
	unsigned int m_id;
	NotificationCallback mCallback;

	static unsigned int msID;
};

#endif