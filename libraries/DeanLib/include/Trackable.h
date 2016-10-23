#ifndef _TRACKABLE_H_
#define _TRACKABLE_H_

#include <iostream>
#include <string>
#include <typeinfo>

class Trackable
{
public:
	void*	operator	new(std::size_t size);
	void	operator	delete(void *ptr);
	void*	operator	new[](std::size_t size);
	void	operator	delete[](void *ptr);

	//for use with placement new
	void*	operator	new(std::size_t size, void* ptr) { return ptr; };
	void	operator	delete(void *ptr, void*ptr2) {};
	void*	operator	new[](std::size_t size, void* ptr) { return ptr; };
	void	operator	delete[](void *ptr, void* ptr2) {};

	virtual bool		equals(const Trackable& other);
	virtual std::size_t getHashCode() const;
	virtual std::string toString() const;
};

#endif