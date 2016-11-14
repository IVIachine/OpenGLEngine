#include "MemoryPool.h"
#include <cstdlib>
#include <assert.h>
#include <iostream>

using namespace std;

//got this algorithm from: http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
int isPowerOfTwo(unsigned int x)
{
	return ((x != 0) && !(x & (x - 1)));
}

unsigned int getClosestPowerOf2LargerThan(unsigned int num)
{
	static size_t powersOf2[32];
	static bool arrayInitted = false;

	//init an array containing all the powers of 2 
	//(as it is static this should only run the first time this function is called)
	if (!arrayInitted)
	{
		for (size_t i = 0; i < 32; i++)
		{
			powersOf2[i] = 1 << i;
		}
	}

	//find the 1st power of 2 which is bigger than or equal to num
	for (size_t i = 0; i < 32; i++)
	{
		if ( powersOf2[i] >= num )
			return powersOf2[i];
	}

	//failsafe
	return 0;
	
}

MemoryPool::MemoryPool(size_t maxNumObjects, size_t objectSize)
{
	//make objectSize a power of 2 - used for padding
	objectSize = getClosestPowerOf2LargerThan(objectSize);
	if (objectSize < 4)
	{
		objectSize = 4;
	}

	//allocate the memory
	mMemory = (Byte*)malloc(objectSize * maxNumObjects);

	//set member variables
	mMaxNumObjects = maxNumObjects;
	mNumAllocatedObjects = 0;
	mObjectSize = objectSize;
	mHighestValidAddress = mMemory + ((maxNumObjects - 1) * objectSize);

	//create the free list
	createFreeList();
}

void MemoryPool::reset()
{
	//clear the free list
	mFreeList.clear();
	//create the free list again
	createFreeList();
	//reset count of allocated objects
	mNumAllocatedObjects = 0;
}

Byte* MemoryPool::allocateObject()
{
	if (mNumAllocatedObjects >= mMaxNumObjects)
	{
		return NULL;
	}

	mNumAllocatedObjects++;
	Byte* ptr = *(mFreeList.begin());
	mFreeList.pop_front();
	return ptr;
}

void MemoryPool::freeObject(Byte* ptr)
{
	//make sure that the address passed in is actually one managed by this pool
	if (ptr >= mMemory && ptr <= mHighestValidAddress)
	{
		//add address back to free list
		mFreeList.push_front(ptr);

		mNumAllocatedObjects--;
	}
	else
	{
		cout << "ERROR:  object freed from a pool that doesn't manage it\n";
		assert(ptr >= mMemory && ptr <= mHighestValidAddress);
	}
}

void MemoryPool::createFreeList()
{
	//  add in reverse order as the forward_list will otherwise be in reverse order
	for (size_t i = mMaxNumObjects - 1;; i--)
	{
		mFreeList.push_front(mMemory + (i * mObjectSize));
		if (i == 0)
			break;
	}

}
