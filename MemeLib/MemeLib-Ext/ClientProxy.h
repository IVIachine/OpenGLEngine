#ifndef _CLIENT_PROXY_H_
#define _CLIENT_PROXY_H_

#include <string>
#include "Net.h"

struct ClientData
{
	std::string name;
	size_t		index;
	NetGUID		guid;
	NetAddress	address;

	ClientData(
		std::string name,
		size_t index, 
		NetGUID guid, 
		NetAddress address)
		: name(name)
		, index(index)
		, guid(guid)
		, address(address)
	{};
};

class ClientProxy
{
public:
	ClientProxy(ClientData data);
	~ClientProxy();

	ClientData	getData() const;
	void		setData(ClientData data);

private:
	ClientData m_data;
};

#endif // !_CLIENT_PROXY_H_
