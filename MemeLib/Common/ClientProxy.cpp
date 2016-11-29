#include "ClientProxy.h"
#include "PaddleServer.h"
#include "Paddle.h"
#include "Ball.h"


ClientProxy::ClientProxy()
{
	m_Registry = new ObjectCreationRegistry();
	m_Registry->RegisterCreationFunction<GameObject>();
	m_Registry->RegisterCreationFunction<Paddle>();
	m_Registry->RegisterCreationFunction<Ball>();
}

ClientProxy::ClientProxy(NetAddress address, NetGUID guid, size_t index, std::string name, uint32_t paddleID)
{
	m_Registry = new ObjectCreationRegistry();
	m_Registry->RegisterCreationFunction<GameObject>();
	m_Registry->RegisterCreationFunction<Paddle>();
	m_Registry->RegisterCreationFunction<Ball>();
	m_address = address;
	m_guid = guid;
	m_index = index;
	m_name = name;
	m_paddleID = paddleID;
}

ClientProxy::ClientProxy(const ClientProxy & copy)
{
}

ClientProxy::~ClientProxy()
{
	delete m_Registry;
	m_Registry = NULL;
}


NetAddress ClientProxy::getAddress() const
{
	return m_address;
}

NetGUID ClientProxy::getGUID() const
{
	return m_guid;
}

size_t ClientProxy::getIndex() const
{
	return m_index;
}

std::string ClientProxy::getName() const
{
	return m_name;
}


void ClientProxy::readMove(BitStream& in)
{
	in.IgnoreBytes(sizeof(RakNet::MessageID));

	float timeStamp;
	in >> timeStamp;

	int counter;
	in >> counter;

	for (int i = 0; i < counter; i++)
	{
		Move tmp;
		tmp.read(in);
		m_moveList.pushBackMove(tmp);
	}

	BitStream oStream;
	oStream.Write((RakNet::MessageID)TIME_PACKET);
	oStream.Write(timeStamp);
	SERVER->sendByAddress(m_address, oStream);
}

void ClientProxy::read(BitStream& in)
{
	in.Read(m_address);
	in.Read(m_guid);
	in.Read(m_index);

	RakNet::RakString rakStr;
	in.Read(rakStr);
	m_name = rakStr.C_String();
}

void ClientProxy::write(BitStream& out) const
{
	out.Write(m_address);
	out.Write(m_guid);
	out.Write(m_index);
	out.Write(m_name.c_str());
}

void ClientProxy::update()
{
	if (static_cast<PaddleServer*>(LINKING->getGameObject(m_paddleID, false, 0, m_Registry)))
	{
		static_cast<PaddleServer*>(LINKING->getGameObject(m_paddleID, false, 0, m_Registry))->updatePaddle(m_moveList);
	}
}
