#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

#include <forward_list>
#include "DeanLibDefines.h"
#include <Trackable.h>


class MemoryPool : public Trackable
{
public:
	MemoryPool(unsigned int maxNumObjects, unsigned int objectSize);
	~MemoryPool() { free(mMemory); };

	void reset();//doesn't reallocate memory but does reset free list and num allocated objects

	Byte* allocateObject();
	void freeObject(Byte* ptr);

	inline size_t getMaxObjectSize() { return mObjectSize; };
	inline size_t getNumFreeObjects() { return mMaxNumObjects - mNumAllocatedObjects; };

private:
	Byte* mMemory;
	Byte* mHighestValidAddress;
	size_t mMaxNumObjects;
	size_t mNumAllocatedObjects;
	size_t mObjectSize;
	std::forward_list<Byte*> mFreeList;

	void createFreeList();
};

#endif // !_MEMORY_POOL_H_
