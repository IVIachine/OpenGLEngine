#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "EventListener.h"
#include <BitStream.h>
#include <RakPeerInterface.h>
#include <fstream>

class GameObjectManager;

typedef size_t GameObjectID;
const static GameObjectID INVALID_GOBJ_ID = 0;

class GameObject : public EventListener
{
public:
	GameObject();
	virtual ~GameObject();

	virtual bool start();
	virtual void destroy();
	virtual void update();
	virtual void draw();
	virtual void handleEvent(const Event& ev);
	
	enum { mClassId = 'GOBJ' };
	virtual uint32_t getClassId() const { return mClassId; };
	static GameObject* createInstance() { return new GameObject(); };

	virtual void sendToServer(RakNet::RakPeerInterface* peer);
	virtual void sendToServer(RakNet::BitStream& stream);
	virtual void read(RakNet::BitStream& stream);
	virtual void write(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);

	GameObjectID getID() const { return m_id; };

private:
	GameObjectID m_id;

	void setID(GameObjectID id) { m_id = id; };

	friend class GameObjectManager;
};



#endif // !_GAME_OBJECT_H_
