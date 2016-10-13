#ifndef _USER_H_
#define _USER_H_

#include <string>

class User
{
public:
	User();
	User(std::string name, std::string addr);
	User(const User& copy);
	~User();

	std::string getAddress() const;
	std::string getName() const;

	void		setAddress(const std::string& addr);
	void		setName(const std::string& name);

private:
	std::string m_name;
	std::string m_address;

};

#endif // !_USER_H_
