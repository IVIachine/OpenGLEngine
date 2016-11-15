#include "ClientProxy.h"

ClientProxy::ClientProxy(ClientData data) : m_data(data)
{
}

ClientProxy::~ClientProxy()
{
}


ClientData ClientProxy::getData() const
{
	return m_data;
}

void ClientProxy::setData(ClientData data)
{
	m_data = data;
}
