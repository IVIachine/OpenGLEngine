#include "UserDatabase.h"

UserDatabase::UserDatabase()
{
	m_userMap = UserMap();
}

UserDatabase::~UserDatabase()
{
}


User* UserDatabase::add(const User& user)
{
	const std::string name = user.getName();

	UserMap::iterator found = m_userMap.find(name);

	if (found == m_userMap.end())
	{
		m_userMap[name] = user;

		return &m_userMap[name];
	}

	return NULL;
}

User* UserDatabase::find(std::string name)
{
	UserMap::iterator found = m_userMap.find(name);

	if (found != m_userMap.end())
	{
		return &found->second;
	}

	return NULL;
}

bool UserDatabase::erase(std::string name)
{
	UserMap::iterator found = m_userMap.find(name);

	if (found != m_userMap.end())
	{
		m_userMap.erase(name);

		return true;
	}

	return false;
}


User* UserDatabase::operator[](std::string name)
{
	return find(name);
}