#ifndef _CLIENT_PROXY_H_
#define _CLIENT_PROXY_H_

#include <string>
#include "Net.h"

class ClientProxy
{
public:
	ClientProxy();
	ClientProxy(NetAddress address, NetGUID guid, size_t index, std::string name);
	ClientProxy(const ClientProxy& copy);
	~ClientProxy();

	NetAddress	getAddress() const;
	NetGUID		getGUID() const;
	std::string getName() const;
	size_t		getIndex() const;

private:
	NetAddress	m_address;
	NetGUID		m_guid;
	size_t		m_index;
	std::string m_name;
};

#endif // !_CLIENT_PROXY_H_
