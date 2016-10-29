#include <iostream>
#include "MemoryTracker.h"
#include <Trackable.h>

using namespace std;

int MemoryTracker::msAllocationNum = 0;
MemoryTracker gMemoryTracker;

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{
	cout << "MemoryTracker being deleted: final allocations follow:\n";
	reportAllocations(cout);
}


void MemoryTracker::addAllocation(Trackable* ptr, size_t size)
{
	//make sure it's not already in the map
	map<Trackable*, AllocationRecord>::iterator iter = mAllocations.find(ptr);
	if (iter != mAllocations.end())
	{
		//already exists - problem!
	}
	else
	{
		AllocationRecord theRec(msAllocationNum, size);
		pair<Trackable*, AllocationRecord> thePair(ptr, theRec);
		mAllocations.insert(thePair);
		msAllocationNum++;
	}
}

Trackable* MemoryTracker::getAllocation(void* ptr)
{
	Trackable* t = reinterpret_cast<Trackable*>(ptr);
	if (t != NULL)
	{
		return t;
	}

	return NULL;
}

void MemoryTracker::removeAllocation(Trackable* ptr)
{
	//find it in the map!
	map<Trackable*, AllocationRecord>::iterator iter = mAllocations.find(ptr);
	if (iter == mAllocations.end())
	{
		//problem!!!!
	}
	else
	{
		mAllocations.erase(iter);
	}
}

void MemoryTracker::reportAllocations(std::ostream& stream)
{
	map<Trackable*, AllocationRecord>::iterator iter;
	for (iter = mAllocations.begin(); iter != mAllocations.end(); ++iter)
	{
		stream
			<< " (" + iter->first->toString() + ")"
			<< " addr:" << iter->first
			<< " size:" << iter->second.size
			<< " num:" << iter->second.num
			<< "\n";
	}
}
