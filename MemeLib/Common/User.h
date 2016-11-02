#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "Serializable.h"

class User : public Serializable
{
public:
	User();
	User(const char* name);
	User(const std::string& name);
	User(const User& copy);
	~User();

	void	deserialize(std::istream& in) override;
	void	serialize(std::ostream& out) const override;

	std::string getName() const;

	friend	bool operator==(const User& lhs, const User& rhs);
	friend	bool operator!=(const User& lhs, const User& rhs);
	friend	bool operator<(const User& lhs, const User& rhs);

private:
	std::string m_name;

};

#endif // !_USER_H_
