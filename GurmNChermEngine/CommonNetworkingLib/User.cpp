#include "User.h"
#include "Net.h"

User::User()
{
	setAddress(LOCAL_HOST);
	setName("User");
}

User::User(std::string name, std::string addr)
{
	setAddress(addr);
	setName(name);
}

User::User(const User& copy)
{
	setAddress(copy.m_address);
	setName(copy.m_name);
}

User::~User()
{
}


std::string User::getAddress() const
{
	return m_address;
}

std::string User::getName() const
{
	return m_name;
}


void User::setAddress(const std::string& addr)
{
	m_address = addr;
}

void User::setName(const std::string& name)
{
	m_name = name;
}