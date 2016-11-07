#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "EventListener.h"
#include <BitStream.h>
#include <RakPeerInterface.h>
#include <fstream>

class GameObjectManager;

class GameObject : public EventListener
{
public:
	virtual bool start();
	virtual void destroy();
	virtual void update();
	virtual void draw();
	virtual void handleEvent(const Event& ev);
	
	enum { mClassId = 'GOBJ' };
	virtual uint32_t getClassId() const { return mClassId; };
	static GameObject* createInstance() { return new GameObject(); };

	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void sendToServer(RakNet::BitStream& stream);
	virtual void read(RakNet::BitStream& stream);
	virtual void write(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of) {};

	GameObject();
	~GameObject();

private:


	friend class GameObjectManager;
};



#endif // !_GAME_OBJECT_H_
