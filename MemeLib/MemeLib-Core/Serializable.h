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
	Serializable() {}
	virtual ~Serializable() {}

	virtual void deserialize(std::istream& in) = 0;
	virtual void serialize(std::ostream& out) const = 0;

	void read(RakNet::BitStream& in);
	void write(RakNet::BitStream& out) const;

	std::stringstream	toStream() const;
	std::string			toString() const;

	friend	std::istream& operator>>(std::istream& in, Serializable& cmd);
	friend	std::ostream& operator<<(std::ostream& out, const Serializable& cmd);

private:
	static const char s_key = '~';
	void unencrypt(std::string& encrypted, const char key) const;
	void encrypt(std::string& unencrypted, const char key) const;
};

#endif // !_SERIALIZABLE_H_
