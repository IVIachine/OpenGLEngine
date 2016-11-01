#ifndef _MEMORY_TRACKER_H_
#define _MEMORY_TRACKER_H_

#include <map>
#include <iostream>

class Trackable;

struct AllocationRecord
{
	AllocationRecord(int theNum, size_t theSize) : num(theNum), size(theSize) {};
	int num;
	size_t size;
};

class MemoryTracker
{
public:
	MemoryTracker();
	~MemoryTracker();

	void		addAllocation(Trackable* ptr, size_t size);
	Trackable*	getAllocation(void* ptr);
	void		removeAllocation(Trackable* ptr);
	void		reportAllocations(std::ostream& stream);

	void		reportFinalAllocations(std::ostream& stream);

private:
	//copying not allowed
	MemoryTracker(const MemoryTracker&);
	MemoryTracker& operator=(const MemoryTracker&);

	std::map<Trackable*, AllocationRecord> mAllocations;

	static int msAllocationNum;
};

extern MemoryTracker gMemoryTracker;

#endif // !_MEMORY_TRACKER_H_
