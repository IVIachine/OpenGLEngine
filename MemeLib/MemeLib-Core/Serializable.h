#ifndef _SERIALIZABLE_H_
#define _SERIALIZABLE_H_

#include <string>
#include <iostream>
#include <sstream>
#include <BitStream.h>
#include <Trackable.h>

class Serializable : public Trackable
{
public:
	Serializable();
	virtual ~Serializable();

	virtual void read(RakNet::BitStream& in) = 0;
	virtual void write(RakNet::BitStream& out) const = 0;
};

#endif // !_SERIALIZABLE_H_
