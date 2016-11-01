#include <iostream>
#include "MemoryTracker.h"
#include <Trackable.h>
#include <sstream>
#include <string>

using namespace std;

int MemoryTracker::msAllocationNum = 0;
MemoryTracker gMemoryTracker;

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{
	reportFinalAllocations(std::cout);
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

void MemoryTracker::reportAllocations(std::ostream& out)
{
	map<Trackable*, AllocationRecord>::iterator iter;
	for (iter = mAllocations.begin(); iter != mAllocations.end(); ++iter)
	{
		out
			<< " (" + iter->first->toString() + ")"
			<< " addr:" << iter->first
			<< " size:" << iter->second.size
			<< " num:" << iter->second.num
			<< "\n";
	}
}


void MemoryTracker::reportFinalAllocations(std::ostream& out)
{
	out << "MemoryTracker being deleted: final allocations follow:\n";

	std::stringstream sstream;
	reportAllocations(sstream);

	if (sstream.str().size() > 0)
	{
		std::cout
			<< "Current memory allocations:\n"
			<< sstream.str();

		system("pause");
	}
	else
	{
		std::cout << "There are no memory allocations.\n";
	}
}
