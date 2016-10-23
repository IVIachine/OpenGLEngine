#include <Trackable.h>
#include "MemoryTracker.h"

void* Trackable::operator new(std::size_t size)
{
	void* ptr = malloc(size);
	gMemoryTracker.addAllocation(gMemoryTracker.getAllocation(ptr), size);
	return ptr;
}

void Trackable::operator delete(void *ptr)
{
	gMemoryTracker.removeAllocation(gMemoryTracker.getAllocation(ptr));
	free(ptr);
}

void* Trackable::operator new[](std::size_t size)
{
	void* ptr = malloc(size);
	gMemoryTracker.addAllocation(gMemoryTracker.getAllocation(ptr), size);
	return ptr;
}

void Trackable::operator delete[](void *ptr)
{
	gMemoryTracker.removeAllocation(gMemoryTracker.getAllocation(ptr));
	free(ptr);
}


bool Trackable::equals(const Trackable& other)
{
	return typeid(*this) == typeid(other);
}

std::size_t Trackable::getHashCode() const
{
	return typeid(*this).hash_code();
}

std::string Trackable::toString() const
{
	return typeid(*this).name();
}