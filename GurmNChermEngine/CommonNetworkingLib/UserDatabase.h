#ifndef _USER_DATABASE_H_
#define _USER_DATABASE_H_

#include <map>
#include "User.h"

typedef std::map<std::string, User> UserMap;

class UserDatabase
{
public:
	UserDatabase();
	~UserDatabase();

	User*	add(const User& user);
	User*	find(std::string name);
	bool	erase(std::string name);

	User*	operator[](std::string name);

private:
	UserMap	m_userMap;
};

#endif // !_USER_DATABASE_H_
