#include "Serializable.h"

void Serializable::read(RakNet::BitStream& in)
{
	RakNet::RakString rakStr;	

	in.Read(rakStr);

	std::string str = rakStr.C_String();

	unencrypt(str, s_key);

	//std::cout << "$ Unencrypted = " << str << "\n";

	std::stringstream sstream(str);

	deserialize(sstream);
}

void Serializable::write(RakNet::BitStream& out) const
{
	std::stringstream sstream;
	
	serialize(sstream);

	std::string str = sstream.str();

	encrypt(str, s_key);

	//std::cout << "$ Encrypted = " << str << "\n";
	
	out.Write(str.c_str());
}


std::stringstream Serializable::toStream() const
{
	std::stringstream sstream;

	serialize(sstream);

	return sstream;
}

std::string Serializable::toString() const
{
	return toStream().str();
}


std::istream& operator>>(std::istream& in, Serializable& msg)
{
	msg.deserialize(in);

	return in;
}

std::ostream& operator<<(std::ostream& out, const Serializable& msg)
{
	msg.serialize(out);

	return out;
}


void Serializable::unencrypt(std::string& input, const char key) const
{
	std::string unencrypted = "";

	for (size_t i = 0; i < input.size(); i++)
	{
		unencrypted += input[i] ^ (int(key) + i) % 255;
	}

	input = unencrypted;
}

void Serializable::encrypt(std::string& input, const char key) const
{
	std::string encrypted = "";

	for (size_t i = 0; i < input.size(); i++)
	{
		encrypted += input[i] ^ (int(key) + i) % 255;
	}

	input = encrypted;
}