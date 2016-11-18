#ifndef _CLIENT_PROXY_H_
#define _CLIENT_PROXY_H_

#include <string>
#include <Serializable.h>
#include "Net.h"
#include "Movelist.h"

class ClientProxy : public Serializable
{
public:
	ClientProxy();
	ClientProxy(NetAddress address, NetGUID guid, size_t index, std::string name, uint32_t paddleID);
	ClientProxy(const ClientProxy& copy);
	~ClientProxy();

	NetAddress	getAddress() const;
	NetGUID		getGUID() const;
	std::string getName() const;
	size_t		getIndex() const;

	void readMove(BitStream& in);
	void read(BitStream& in) override;
	void write(BitStream& out) const override;
	void update();

private:
	NetAddress	m_address;
	NetGUID		m_guid;
	uint32_t	m_paddleID;
	size_t		m_index;
	std::string m_name;
	MoveList m_moveList;
};

#endif // !_CLIENT_PROXY_H_