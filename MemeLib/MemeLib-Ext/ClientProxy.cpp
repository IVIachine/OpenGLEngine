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
