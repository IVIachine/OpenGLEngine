#include "ClientProxy.h"

ClientProxy::ClientProxy()
{
}

ClientProxy::ClientProxy(NetAddress address, NetGUID guid, size_t index, std::string name)
{
	m_address = address;
	m_guid = guid;
	m_index = index;
	m_name = name;
}

ClientProxy::ClientProxy(const ClientProxy & copy)
{
}

ClientProxy::~ClientProxy()
{
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
