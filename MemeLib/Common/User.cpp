#include "User.h"

User::User()
{
	m_name = "User";
}

User::User(const char* name)
{
	deserialize(std::stringstream(name));
}

User::User(const std::string& name)
{
	deserialize(std::stringstream(name));
}

User::User(const User& copy)
{
	deserialize(copy.toStream());
}

User::~User()
{
}


void User::deserialize(std::istream& in)
{
	in >> m_name;
}

void User::serialize(std::ostream& out) const
{
	out << m_name.c_str();
}


std::string User::getName() const
{
	return m_name;
}


bool operator==(const User& lhs, const User& rhs)
{
	return lhs.toString() == rhs.toString();
}

bool operator!=(const User& lhs, const User& rhs)
{
	return lhs.toString() != rhs.toString();
}

bool operator<(const User& lhs, const User& rhs)
{
	return lhs.toString() < rhs.toString();
}